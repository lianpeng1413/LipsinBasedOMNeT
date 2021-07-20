/*
 * NlsrNeighbor.h
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 *
 *  Represents another node that we expect to be running NLSR that
 *  we should be able to reach over a direct face connection.
 */

#ifndef INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBOR_H_
#define INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBOR_H_

#include <list>
#include <string>
#include <cmath>

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/PSync/detail/iblt.h"
#include "inet/routing/nlsr/messageHandler/SyncHandler.h"

namespace inet {

namespace nlsr {

class NeighborState;
class NlsrInterface;
class SyncHandler;

typedef std::function<void(const std::vector<MissingDataInfo>&)> UpdateCallback;

//const simtime_t SYNC_INTEREST_LIFTIME = 1000;

class INET_API Neighbor
{
    friend class NeighborState;

  public:
    enum NeighborEventType {
        HELLO_DATA_RECEIVED     = 0,
        SYNC_TIMER              = 1,
        EXCHANGE_DONE           = 2,
        INACTIVITY_TIMER        = 3,
        KILL_NEIGHBOR           = 4,
        LINK_DOWN               = 5,
        LOADING_DONE            = 6,
        SYNC_RECEIVED           = 7,
        SEQUENCE_NUMBER_MISMATCH = 8
    };

    enum NeighborStateType {
        DOWN_STATE     = 0,
        EXCHANGE_STATE = 1,  // active state
        FULL_STATE     = 2   // active state

    };

    static const double DEFAULT_LINK_COST;
    static const double NON_ADJACENT_COST;

  private:
    NeighborState *state = nullptr;
    NeighborState *previousState = nullptr;
    cMessage *inactivityTimer = nullptr; //Used to decide whether neighbor active or not.
    iName neighborName;
    NlsrInterface *parentInterface = nullptr;
    bool firstAdjacencyInited = false;
    short neighborsRouterDeadInterval = 0;
    short syncInterval;
    double m_linkCost = 1;
    cMessage *syncTimer;
    iName m_outstandingInterestName;
    SyncHandler *syncHandler;

  private:
    void changeState(NeighborState *newState, NeighborState *currentState);

  public:
    Neighbor(RouterName neighbor);
    virtual ~Neighbor();

    void processEvent(NeighborEventType event);
    void reset();
    void initFirstAdjacency();
    NeighborStateType getState() const;
//    void setStatus(NeighborStateType s){ m_status = s; }
    static const char *getStateString(NeighborStateType stateType);
    double getLinkCost() const { return m_linkCost; }

    void setLinkCost(double lc) { m_linkCost = lc;}
    /* Sends the sync interest */
    void sendSyncInterestPacket();
    void setSyncHandler(SyncHandler *sync) { syncHandler = sync; }
    void setNeighborName(RouterName id) { neighborName = id; }
    iName getNeighborName() const { return neighborName; }
    void setRouterDeadInterval(short interval) { neighborsRouterDeadInterval = interval; }
    short getRouterDeadInterval() const { return neighborsRouterDeadInterval; }
    void setInterface(NlsrInterface *intf) { parentInterface = intf; }
    NlsrInterface *getInterface() { return parentInterface; }
    const NlsrInterface *getInterface() const { return parentInterface; }
    cMessage *getInactivityTimer() { return inactivityTimer; }
    cMessage *getSyncTimer() { return syncTimer; }
    void setSyncInterval(short interval) { syncInterval = interval; }
    short getSyncInterval() const { return syncInterval; }

    /*! \brief Equality is when name, Face ID, and link cost are all equal. */
    bool operator==(const Neighbor& adjacent) const;
    bool operator!=(const Neighbor& adjacent) const { return !(*this == adjacent); }
    bool operator<(const Neighbor& adjacent) const;

    inline bool compare(const iName& adjacencyName) const { return neighborName == adjacencyName; }
    friend std::ostream& operator<<(std::ostream& os, const Neighbor& adjacent);
};

std::ostream& operator<<(std::ostream& os, const Neighbor& adjacent);

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBOR_H_ */
