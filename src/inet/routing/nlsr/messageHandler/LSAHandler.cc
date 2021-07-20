/*
 * LSAHandler.cc
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/messageHandler/LSAHandler.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/linklayer/common/MacAddressTag_m.h"

namespace inet {
namespace nlsr {

LSAHandler::LSAHandler(Router *containingRouter): IMessageHandler(containingRouter)
{
}

void LSAHandler::processPacket(Packet *packet, NlsrInterface *intf, Neighbor *neighbor)
{
    router->getMessageHandler()->printEvent("LSA packet received", intf, neighbor);

    const auto& head = packet->peekAtFront<NlsrPacket>();
    NlsrPacketType packetType = static_cast<NlsrPacketType>(head->getType());

    switch (packetType) {
    case ADJ_LSA_INTEREST:
        processInterestForAdjLsa(packet, intf, neighbor);
        break;

    case ADJ_LSA_DATA:
        processContentAdjLsa(packet, intf, neighbor);
        break;

    case NAME_LSA_INTEREST:
        processInterestForNameLsa(packet, intf, neighbor);
        break;

    case NAME_LSA_DATA:
        processContentNameLsa(packet, intf, neighbor);
        break;

    default:
        break;
    }
}

/* Finds and sends a requested adj LSA. */
void LSAHandler::processInterestForAdjLsa(Packet *packet, NlsrInterface *intf, Neighbor *neighbor)
{ // RCV_ADJ_LSA_INTEREST
//    packet->trim();  // some operate of packet header

    const auto head = packet->peekAtFront<AdjLsaInterest>();
    const iName &interest = head->getInterestName();

    EV_INFO << "AdjLsa interest " << interest.str() << " received.\n";

    unsigned long interestCount = head->getInterestsArraySize();

    // Get interest name and put it into pendingSyncAdjName.
    for(unsigned long i = 0; i < interestCount; i++){
        const auto& adjLsa = head->getInterests(i);

        EV_INFO << "LsaInterest:" << adjLsa.interestName << "\n";

        //Generate adjData packet and put LSA info into it.
        iName adjLsaDataName;
        adjLsaDataName.set(interest.getTail(), "ADJLSADATA", interest.getTag());

        const auto& data = makeShared<AdjDataPacket>();
        data->setInterestName(adjLsaDataName);
        data->setVersion(2);
        data->setType(ADJ_LSA_DATA);

        auto adjLSA = router->findAdjLsa(adjLsa.interestName);

        EV_INFO << "AdjLsa interest " << interest.str() << " received.\n";

        //If there's name need to sync, then send syncData, otherwise put it into m_pendingEntries.
        EV_INFO << "Sending adj data: " << adjLsaDataName.str() << ".\n";
        data->setAdjLSA(adjLSA);
        Packet *pkt = new Packet("syncAdjLsaData");

        pkt->insertAtFront(data);

        iName neighbors;
        std::string neighborName;
        neighborName += interest.getTail();  //Get neighbor name
        neighbors.transName(neighborName);
        MessageHandler *messageHandler = router->getMessageHandler();
        messageHandler->sendPacket(pkt, neighbors, intf, 1);
        pkt->trim();
        delete pkt;
        return;
    }
}

// process received adj LSA data packet, and trigger LSDB update.
void LSAHandler::processContentAdjLsa(Packet *packet, NlsrInterface *intf, Neighbor *neighbor)
{
    EV_INFO << "Adj Lsa Data Packet Received." << endl;

    if(neighbor != nullptr){//TODO
        Neighbor::NeighborStateType neighborState = neighbor->getState();
        if ((neighborState == Neighbor::EXCHANGE_STATE) ||
            (neighborState == Neighbor::FULL_STATE))
        {
            packet->trim();  // some operate of packet header
            const auto head = packet->peekAtFront<AdjDataPacket>();

            EV_INFO << "  Processing adj lsa packet contents:\n";

            auto adjLSA = head->getAdjLSA();
            iName lsaName = head->getAdjLSA()->getHeader().getInterestName();
            long seqNo = head->getAdjLSA()->getHeader().getSeqNo();
            if (router->isAdjLsaNew(lsaName, seqNo)) {
                router->installAdjLsa(adjLSA);
            }
        }
        if(intf->getWhetherFull())
            neighbor->processEvent(Neighbor::EXCHANGE_DONE);
    }
    else{
        packet->trim();  // some operate of packet header
        const auto head = packet->peekAtFront<AdjDataPacket>();

        EV_INFO << "  Processing adj lsa packet contents:\n";

        auto adjLSA = head->getAdjLSA();
        iName lsaName = head->getAdjLSA()->getHeader().getInterestName();
        long seqNo = head->getAdjLSA()->getHeader().getSeqNo();
        if (router->isAdjLsaNew(lsaName, seqNo)) {
            router->installAdjLsa(adjLSA);
        }
    }
}

/* Process a requested name LSA. */
void LSAHandler::processInterestForNameLsa(Packet *packet, NlsrInterface *intf, Neighbor *neighbor)
{// Process RCV_NAME_LSA_INTEREST
    packet->trim();  // some operate of packet header

    const auto head = packet->peekAtFront<NameLsaInterest>();
    const iName &dataName = head->getInterestName();

    EV_INFO << "Name Lsa interest " << dataName.str() << " received";

    unsigned long interestCount = head->getInterestsArraySize();

    // Get interest name and put it into pendingSyncNameLsaName.
    for(unsigned long i = 0; i < interestCount; i++){
        const auto& nameLsa = head->getInterests(i);
        EV_INFO << "LsaInterest: type=" << nameLsa.lsType << ", interest name=" << nameLsa.interestName << "\n";

        //Generate adjData packet and put LSA info into it.
        iName nameLsaDataName;
        nameLsaDataName.set(dataName.getTail(), "NAMELSADATA", dataName.getTag());

        const auto& data = makeShared<NameDataPacket>();
        data->setInterestName(nameLsaDataName);
        data->setVersion(2);
        data->setType(NAME_LSA_DATA);

        auto nameLSA = router->findNameLsa(nameLsa.interestName); // Get NlsrNameLsa

        //If there's name need to sync, then send syncData, otherwise put it into m_pendingEntries.
        EV_INFO << "Sending name data: " << nameLsaDataName.str() << "\n";
        data->setNameLSA(nameLSA);

        Packet *pkt = new Packet("syncNameData");
        pkt->insertAtFront(data);

        iName nextNode;
        std::string neighborName;
        neighborName += dataName.getTail();  //Get neighbor name
        EV_INFO << "send name Data packet to neighbor: " << neighborName << endl;
        nextNode.transName(neighborName);

        MessageHandler *messageHandler = router->getMessageHandler();
        messageHandler->sendPacket(pkt, nextNode, intf, 1);
        delete pkt;
        return;
    }
}

/* process received name LSA data packet, and trigger LSDB update.*/
void LSAHandler::processContentNameLsa(Packet *packet, NlsrInterface *intf, Neighbor *neighbor)
{
    EV_INFO << "Name Lsa Data Packet Received." << endl;
    if(neighbor != nullptr){//TODO
        Neighbor::NeighborStateType neighborState = neighbor->getState();

        if ((neighborState == Neighbor::EXCHANGE_STATE) ||
            (neighborState == Neighbor::FULL_STATE))
        {
            packet->trim();  // some operate of packet header
            const auto head = packet->peekAtFront<NameDataPacket>();

            EV_INFO << "  Processing name lsa data packet contents:\n";

            const NlsrNameLsa *nameLsa = head->getNameLSA();  //Extract nameLSA from packet.
            iName lsaName = nameLsa->getHeader().getInterestName();//Get lsa name.
            long seqNo = nameLsa->getHeader().getSeqNo(); //Get seqNo

            if (router->isNameLsaNew(lsaName, seqNo)) {
                router->installNameLsa(nameLsa); //Install new name lsa into LSDB.
            }
        }

        if(intf->getWhetherFull())
            neighbor->processEvent(Neighbor::EXCHANGE_DONE);
    }
    else{
        packet->trim();  // some operate of packet header
        const auto head = packet->peekAtFront<NameDataPacket>();

        EV_INFO << "  Processing name lsa data packet contents:\n";

        const NlsrNameLsa *nameLsa = head->getNameLSA();  //Extract nameLSA from packet.
        iName lsaName = nameLsa->getHeader().getInterestName();//Get lsa name.
        long seqNo = nameLsa->getHeader().getSeqNo(); //Get seqNo

        if (router->isNameLsaNew(lsaName, seqNo)) {
            router->installNameLsa(nameLsa); //Install new name lsa into LSDB.
        }
    }
}

} // namespace nlsr
} // namespace inet



