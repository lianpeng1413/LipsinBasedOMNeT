/*
 * NlsrNeighbor.cc
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */

#include <memory.h>

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborState.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborStateDown.h"

#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet {
namespace nlsr {

using namespace nlsr;

const double Neighbor::DEFAULT_LINK_COST = 10.0;
const double Neighbor::NON_ADJACENT_COST = -12345;

Neighbor::Neighbor(RouterName neighbor):
        neighborName(neighbor),
        neighborsRouterDeadInterval(10)
{
    inactivityTimer = new cMessage("Neighbor::NeighborInactivityTimer", NEIGHBOR_INACTIVITY_TIMER);
    inactivityTimer->setContextPointer(this);
//    syncInterval = ;  //setting syncInterval by .ini file.
    syncInterval = 1;  // TODO default value 60s, valid values 1s~120s. we set 10s.
    syncTimer = new cMessage("Neighbor::SyncTimer", SYNC_START_TIMER);
    syncTimer->setContextPointer(this);

    state = new NeighborStateDown; // neighbor state is down at start stage
    previousState = nullptr;
}

Neighbor::~Neighbor()
{
    reset();
//    if(parentInterface && parentInterface->getArea()) {
//        MessageHandler *messageHandler = parentInterface->getArea()->getRouter()->getMessageHandler();
//        messageHandler->clearTimer(inactivityTimer);
//        messageHandler->clearTimer(syncTimer);
//    }
    delete inactivityTimer;
    delete syncTimer;
    if (previousState)
        delete previousState;
    delete state;
}

void Neighbor::changeState(NeighborState *newState, NeighborState *currentState)
{
    EV_INFO << "Changing neighborhood state of " << this->getNeighborName().str() <<
            " from '" << getStateString(currentState->getState()) <<
            "' to '" << getStateString(newState->getState()) << "'" << std::endl;

    if (previousState != nullptr) {
        delete previousState;
    }
    state = newState;
    previousState = currentState;
}

void Neighbor::processEvent(Neighbor::NeighborEventType event)
{
    state->processEvent(this, event);
}

// clear some timers and neighbor infor.
void Neighbor::reset()
{
    if(parentInterface && parentInterface->getArea()) {
        MessageHandler *messageHandler = parentInterface->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(inactivityTimer);
        messageHandler->clearTimer(syncTimer);
    }
}

void Neighbor::initFirstAdjacency()
{
    firstAdjacencyInited = true;
}

Neighbor::NeighborStateType Neighbor::getState() const
{
    return state->getState();
}

const char *Neighbor::getStateString(Neighbor::NeighborStateType stateType)
{
    switch (stateType) {
        case DOWN_STATE:
            return "Down";

        case EXCHANGE_STATE:
            return "Exchange";

        case FULL_STATE:
            return "Full";

        default:
            ASSERT(false);
            break;
    }
    return "";
}

void Neighbor::sendSyncInterestPacket()
{ // Sync Interest format for full sync: /Neighbor/NLSRSYNC/localRouter
    EV_INFO << "Send sync interest packet to all neighbor." << endl;

    iName syncInterestName;
    std::string tag, tail;
    tag.append(neighborName.str());
    tail.append(parentInterface->getArea()->getRouter()->getRouterID().str());
    syncInterestName.set(tag.erase(0, 1), "SYNC", tail.erase(0, 1));
    EV_INFO << neighborName.str() << ", sync interest name: " << syncInterestName.str() << endl;

    const auto& syncInterests = makeShared<syncInterest>();
    syncInterests->setInterestName(syncInterestName);
    syncInterests->setVersion(2);
    syncInterests->setType(SYNC_INTEREST);

    // Computing our latest IBLT and add it into sync packet
    syncInterests->setM_iblt(syncHandler->generateIBLT());

    Packet *pk = new Packet("syncInterest");
    pk->insertAtFront(syncInterests);

    MessageHandler *messageHandler = parentInterface->getArea()->getRouter()->getMessageHandler();
    int ttl = 1;
    iName destination;
    destination.set("NLSR", "ROUTERS", "MULTICAST");
    messageHandler->sendPacket(pk, destination, parentInterface, ttl);
    pk->trim();
    delete pk;
}

} // namespace nlsr
} // namespace inet



