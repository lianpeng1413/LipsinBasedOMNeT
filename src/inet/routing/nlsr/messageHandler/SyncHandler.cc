/*
 * SyncHandler.cc
 *
 *  Created on: Oct 6, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/messageHandler/SyncHandler.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"

namespace inet {
namespace nlsr {

SyncHandler::SyncHandler(Router *containingRouter): IMessageHandler(containingRouter)
    ,m_iblt(expectedNumEntries)
    ,m_expectedNumEntries(expectedNumEntries)
    ,m_threshold(expectedNumEntries/2)
{
}

/* Processes a sync interest packet from a neighbor. LSA: nameLSA and adjLSA.*/
void SyncHandler::processPacket(Packet *packet, NlsrInterface *intf, Neighbor *unused2)
{
    EV_INFO << "sync Packet Received." << endl;
    const auto& head = packet->peekAtFront<NlsrPacket>();
    NlsrPacketType packetType = static_cast<NlsrPacketType>(head->getType());

    switch (packetType) {
    case SYNC_INTEREST:
        processSyncInterestPacket(packet, intf, unused2);
        break;

    case SYNC_DATA:
        processSyncDataPacket(packet, intf, unused2);
        break;

    default:
        break;
    }
}

//* process sync interest. */
void SyncHandler::processSyncInterestPacket(Packet *packet, NlsrInterface *intf, Neighbor *unused2)
{ // RCV_SYNC_INTEREST
    packet->trim();  // some operate of packet header

    //Get sync interest packet header
    const auto head = packet->peekAtFront<syncInterest>();
    const iName &interestName = head->getInterestName();

    EV_INFO << "Sync interest '" << interestName.str() << "' received" << endl;

    auto ibltReceived = head->getM_iblt(); //Get iblt from sync packet
    IBLT iblt(m_expectedNumEntries);
    m_iblt = generateIBLT();
    IBLT diff = m_iblt - ibltReceived; // Get the difference

    std::set<uint32_t> positive;
    std::set<uint32_t> negative;

    pendingSyncDataName.clear();

    if (!diff.listEntries(positive, negative)) {
        EV_INFO << "Cannot decode differences, positive: " << positive.size()
                << " negative: " << negative.size() << " m_threshold: " << m_threshold << endl;
        // Send all data if greater then threshold, else send positive below as usual
        // Or send if we can't get neither positive nor negative differences
        if (positive.size() + negative.size() >= m_threshold ||
            (positive.size() == 0 && negative.size() == 0)) {
          State state;
          for (const auto& content : m_prefixes) {
              std::string  tag, prefix, tail;
              tail = content.first.getTail();
              tail.append(std::to_string(content.second));
              iName contents;
              contents.set(content.first.getTag(), content.first.getPrefix(), tail);
              state.addContent(contents);
              pendingSyncDataName.push_back(contents);
          }
        }
    }

    // Find differences and put them into pendingSyncDataName.
    State state;
    for (auto& hash : positive) {
        auto nameIt = m_biMap.left.find(hash);
        if (nameIt != m_biMap.left.end()) {
            iName nameWithSeq = nameIt->second;
            pendingSyncDataName.push_back(nameWithSeq);
            EV_INFO << "name put into pendingSync: " << nameWithSeq.str()<< endl;
            state.addContent(nameWithSeq);
        }
    }

    if(!pendingSyncDataName.empty()){
        sendSyncDataPacket(interestName, intf);    //send sync data
    }
    else
        auto& entry = m_pendingEntries.emplace(interestName, PendingEntryInfoFull{ibltReceived, intf}).first->second; //TODO ADD TIMEOUT RECORDER
}

void SyncHandler::satisfyPendingInterests()
{
    EV_INFO << "Satisfying full sync interest: " << m_pendingEntries.size();
    for (auto it = m_pendingEntries.begin(); it != m_pendingEntries.end();) {
      const PendingEntryInfoFull& entry = it->second;
      IBLT diff = m_iblt - entry.iblt;
      std::set<uint32_t> positive;
      std::set<uint32_t> negative;

      m_pendingEntriesResponse.clear();

      if (!diff.listEntries(positive, negative)) {
        EV_INFO << "Decode failed for pending interest" << endl;
        if (positive.size() + negative.size() >= m_threshold ||
            (positive.size() == 0 && negative.size() == 0)) {
          EV_INFO << "pos + neg > threshold or no diff can be found, erase pending interest" << endl;
          it = m_pendingEntries.erase(it);
          continue;
        }
      }

      State state;
      for (const auto& hash : positive) {
        auto nameIt = m_biMap.left.find(hash);
        if (nameIt != m_biMap.left.end()) {
            iName nameWithSeq = nameIt->second;
            m_pendingEntriesResponse.push_back(nameWithSeq);
            EV_INFO << "name put into pendingSync: " << nameWithSeq.str()<< endl;
          }
        }
      if(!m_pendingEntriesResponse.empty()){
          if(it->second.intf != nullptr){
              sendSyncData(it->first, it->second.intf);    //send back sync data
          }
          it = m_pendingEntries.erase(it);
      }
      else{
          ++it;
      }
    }
}

void SyncHandler::sendSyncData(iName interestName, NlsrInterface *intf)
{
    // Generate sync data, add "lsa name" to data packet
    // Sync data name format: /Neighbor/NLSRSYNC/localRouter
    iName syncDataName;
    syncDataName.set(interestName.getTail(), interestName.getPrefix(), this->router->getRouterID().str().erase(0, 1));
    const auto& data = makeShared<syncData>();
    data->setInterestName(syncDataName);
    data->setVersion(2);
    data->setChunkLength(B(1000));
    data->setMoreFragments(false);

    B maxPacketSize = NLSR_SYNC_DATA_LENGTH;
    B packetSize = NLSR_HEADER_LENGTH + B(18);

    //If there's name need to sync, then send syncData, otherwise put it into m_pendingEntries.
    if(!m_pendingEntriesResponse.empty()) {
        auto it = m_pendingEntriesResponse.begin();
        while((it != m_pendingEntriesResponse.end()) && (packetSize <= (maxPacketSize - NLSR_HEADER_LENGTH - B(18)))) {
            unsigned long syncNameCount = data->getSyncDATAArraySize();
            iName pendingSyncName = *it;
            data->setSyncDATAArraySize(syncNameCount + 1);
            data->setSyncDATA(syncNameCount, pendingSyncName);
            iName neighborName;
            neighborName.set(interestName.getTail());
            packetSize += INAME_LENGTH;
            it++;
        }

        data->setPacketLengthField(B(packetSize).get());
        data->setChunkLength(NLSR_SYNC_DATA_LENGTH);

        Packet *pkt = new Packet("syncInterest");

        pkt->insertAtFront(data);

        iName neighborName;
        neighborName.set(interestName.getTail());

        MessageHandler *messageHandler = router->getMessageHandler();
        messageHandler->sendPacket(pkt, neighborName, intf, 1);
        pkt->trim();
        delete pkt;
        return;
    }
}

void SyncHandler::sendSyncDataPacket(iName interestName, NlsrInterface *intf)
{
    // Generate sync data, add "lsa name" to data packet
    iName syncDataName;
    syncDataName.set(interestName.getTail(), interestName.getPrefix(), this->router->getRouterID().str().erase(0, 1));
    const auto& data = makeShared<syncData>();
    data->setInterestName(syncDataName);
    data->setVersion(2);
    data->setChunkLength(B(1000));
    data->setMoreFragments(false);

    B maxPacketSize = NLSR_SYNC_DATA_LENGTH;
    B packetSize = NLSR_HEADER_LENGTH + B(18);

    //If there's name need to sync, then send syncData, otherwise put it into m_pendingEntries.
    if(!pendingSyncDataName.empty()) {
        auto it = pendingSyncDataName.begin();
        while((it != pendingSyncDataName.end()) && (packetSize <= (maxPacketSize - NLSR_HEADER_LENGTH - B(18)))) {
            unsigned long syncNameCount = data->getSyncDATAArraySize();
            iName pendingSyncName = *it;
            data->setSyncDATAArraySize(syncNameCount + 1);
            data->setSyncDATA(syncNameCount, pendingSyncName);
            iName neighborName;
            neighborName.set(interestName.getTail());
            packetSize += INAME_LENGTH;
            it++;
        }

        data->setPacketLengthField(B(packetSize).get());
        data->setChunkLength(NLSR_SYNC_DATA_LENGTH);

        Packet *pkt = new Packet("syncInterest");

        pkt->insertAtFront(data);

        iName neighborName;
        neighborName.set(interestName.getTail());

        MessageHandler *messageHandler = router->getMessageHandler();
        messageHandler->sendPacket(pkt, neighborName, intf, 1);
        delete pkt;
        return;
    }
}

/* Process incoming sync data. whenever incoming data is verified. */
void SyncHandler::processSyncDataPacket(Packet *packet, NlsrInterface *intf, Neighbor *neighbor)
{// Receive packet, parsing packet, get packet name and interest names.
    router->getMessageHandler()->printEvent("sync data packet received", intf, neighbor);

    packet->trim();  // some operate of packet header
    const auto head = packet->peekAtFront<syncData>();
    const iName &syncDataName = head->getInterestName();
    deletePendingInterests(syncDataName);

    unsigned long nameCount = head->getSyncDATAArraySize();

    EV_INFO << "  Processing packet contents:\n";

    for (unsigned long i = 0; i < nameCount; i++) {
        auto requrestDataName = head->getSyncDATA(i);  // requestDataName with seqNo.
        iName nameWithoutSeq; // request data name in neighbor lsdb.
        long seqNo;           // get the request name seqNo.
        std::string tail, seq;
        tail = requrestDataName.getTail();
        seq = tail.substr(1); // get the substring from second place to the end.
        seqNo = std::stol(seq); // string to long.
        tail = tail.substr(0, 1); // get tail without seqNo.
        nameWithoutSeq.set(requrestDataName.getTag(), requrestDataName.getPrefix(), tail);

        EV_INFO << "pending sync interest name with seqNo in data packet: " << requrestDataName.str() << "\n"
                << "request Data Name without seqNo: " << nameWithoutSeq.str() <<" , seqNo: "<< seqNo << endl;
        if (requrestDataName.getPrefix() == "ADJLSA") {
            intf->addToPendingRequestAdjLsaNameList(nameWithoutSeq);
        }
        else {
            intf->addToPendingRequestNameLsaNameList(nameWithoutSeq);
        }

        intf->sendAdjLSAInterestPacket(nameWithoutSeq, syncDataName, 1, neighbor);
        intf->sendNameLSAInterestPacket(nameWithoutSeq, syncDataName, 1, neighbor);
    }
    if(neighbor != nullptr)
        neighbor->processEvent(Neighbor::SYNC_RECEIVED);
}

bool SyncHandler::isFutureHash(const iName& prefix, const std::set<uint32_t>& negative)
{
    int number = m_prefixes[prefix]+1;
    iName nPrefix;

    std::string tag = prefix.getTag();
    std::string tail = prefix.getTail();
    std::string pre = prefix.getPrefix();
    tail = tail + std::to_string(number);

    nPrefix.set(tag, pre, tail);

    uint32_t nextHash = murmurHash3(N_HASHCHECK, nPrefix.str());
    for (const auto& nHash : negative) {
        if (nHash == nextHash) {
            return true;
            break;
        }
    }
    return false;
}

void SyncHandler::deletePendingInterests(const iName& interestName)
{
    auto it = m_pendingEntries.find(interestName);
    if (it != m_pendingEntries.end()) {
        EV_INFO << "Delete pending interest: " << interestName << endl;
        it = m_pendingEntries.erase(it);
    }
}

void SyncHandler::gatherLsdbNames()
{
    m_prefixes.clear();
    auto adjLsdb = router->getAdjLsdb();
    for (auto adjLsa : adjLsdb)
    {
        iName adjWithoutSeq = adjLsa->getHeader().getInterestName();
        long adjSeq = adjLsa->getHeader().getSeqNo();
        m_prefixes.emplace(adjWithoutSeq, adjSeq);
        EV_INFO << "put adj into PT:" << adjWithoutSeq.str() << endl;
    }

    auto nameLsdb = router->getNameLsdb();
    for (auto nameLsa : nameLsdb)
    {
        iName nameWithoutSeq = nameLsa->getHeader().getInterestName();
        long nameSeq = nameLsa->getHeader().getSeqNo();
        m_prefixes.emplace(nameWithoutSeq, nameSeq);
        EV_INFO << "put name into PT:" << nameWithoutSeq.str() << endl;
    }
}

long SyncHandler::getSeqNo(const iName& prefix) const
{
    auto it = m_prefixes.find(prefix);
    if (it == m_prefixes.end()) {
        return 0;
    }
    return it->second;
}

IBLT SyncHandler::generateIBLT()
{
    EV_INFO << "Update IBF." << endl;
    gatherLsdbNames();

    // Delete the last m_biMap infor.
    auto hashIt = m_biMap.right.begin();
    if(hashIt != m_biMap.right.end()){
        m_biMap.right.erase(hashIt);
    }

    //Delete the last iblt info.
    for (auto& entry : m_iblt.m_hashTable) {
        entry.count = 0;
        entry.keyCheck = 0;
        entry.keySum = 0;
    }

    // Insert the new name from m_prefixes to m_biMap and m_iblt.
    auto it = m_prefixes.begin();
    for (; it != m_prefixes.end(); it++)
    {
        iName prefixWithoutSeq = it->first;
        long seqNo = it->second;
        iName prefixWithSeq;
        std::string tail;
        tail = prefixWithoutSeq.getTail();
        tail.append(std::to_string(seqNo));
        prefixWithSeq.set(prefixWithoutSeq.getTag(), prefixWithoutSeq.getPrefix(), tail);
        uint32_t newHash = murmurHash3(N_HASHCHECK, prefixWithSeq.str());
        m_biMap.insert({newHash, prefixWithSeq});
        m_iblt.insert(newHash);
    }
    return m_iblt;
}

} // namespace nlsr
} // namespace inet





