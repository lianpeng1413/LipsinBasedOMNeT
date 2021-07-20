/*
 * SyncHandler.h
 *
 *  Created on: Oct 6, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_MESSAGEHANDLER_SYNCHANDLER_H_
#define INET_ROUTING_NLSR_MESSAGEHANDLER_SYNCHANDLER_H_

#include <map>
#include <iostream>
#include <random>
#include <cstring>
#include <limits>
#include <functional>
#include <string.h>
#include <string>
#include <cstdio>
#include <atomic>

#include "inet/common/INETDefs.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/common/packet/Packet.h"
#include "inet/routing/nlsr/PSync/detail/state.h"
#include "inet/routing/nlsr/PSync/detail/accessSpecifiers.h"
#include "inet/routing/nlsr/PSync/detail/bloomFilter.h"
#include "inet/routing/nlsr/PSync/detail/iblt.h"
#include "inet/routing/nlsr/PSync/detail/util.h"
#include "inet/routing/nlsr/messageHandler/IMessageHandler.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"

#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

namespace inet {

namespace nlsr {

class NlsrInterface;

namespace bm = boost::bimaps;
//const simtime_t SYNC_REPLY_FRESHNESS = 1000;

struct PendingEntryInfoFull
{
  IBLT iblt;
  inet::nlsr::NlsrInterface *intf;
};

using HashNameBiMap = boost::bimaps::bimap<boost::bimaps::unordered_set_of<uint32_t>,
                                           boost::bimaps::unordered_set_of<iName, std::hash<iName>>>;

class INET_API SyncHandler : public IMessageHandler
{
private:
    simtime_t m_lsaRefreshTime;

public:
    int expectedNumEntries = 80;    //default value is:80, in sync-protocol-adapter.cpp
    IBLT m_iblt;
    int m_expectedNumEntries;
    // Threshold is used check if the differences are greater than it and whether we need to update the other side.
    int m_threshold;
    std::map<iName, long> m_prefixes; // prefix and sequence number
    HashNameBiMap m_biMap;

    int m_face;
    iName m_syncPrefix;
//    std::vector<iName *> pendingRequestAdjLsaName;
//    std::vector<iName *> pendingRequestNameLsaName;
    std::map<iName, PendingEntryInfoFull> m_pendingEntries;
    std::vector<iName> pendingSyncDataName;
    std::vector<iName> m_pendingEntriesResponse;

public:
    SyncHandler(Router *containingRouter);

    void processPacket(Packet *pk, NlsrInterface *intf, Neighbor *neighbor);

    /* Processes a sync interest packet from a neighbor.*/
    void processSyncInterestPacket(Packet *packet, NlsrInterface *intf, Neighbor *neighbor);

    /** Satisfy pending sync interests.
     * For pending sync interests SI, if IBF of SI has any difference from our own IBF:
     * send data back. otherwise, delete it. */
    void satisfyPendingInterests();

    /* Process pending sync interests to send sync data back.*/
    void sendSyncData(iName interestName, NlsrInterface *intf);

    /* Process incoming sync data.*/
    void sendSyncDataPacket(iName interestName, NlsrInterface *intf);

    /* Process incoming sync data.*/
    void processSyncDataPacket(Packet *dataPacket, NlsrInterface *intf, Neighbor *neighbor);

    /** Delete pending sync interests that match given name */
    void deletePendingInterests(const iName& interestName);

     /** Check if hash(prefix + 1) is in negative
     * Sometimes what happens is that interest from other side gets to us before the data */
    bool isFutureHash(const iName& prefix, const std::set<uint32_t>& negative);

    /** Gather names together which extract from lsdb*/
    void gatherLsdbNames();

    /** Returns the current sequence number of the given prefix*/
    long getSeqNo(const iName& prefix) const;

    /**  update m_biMap, and IBF   */
    IBLT generateIBLT();
};

} // namespace NLSR

} // namespace inet



#endif /* INET_ROUTING_NLSR_MESSAGEHANDLER_SYNCHANDLER_H_ */
