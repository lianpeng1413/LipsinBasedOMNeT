/*
 * NeighborState.cc
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */


#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborStateDown.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborStateExchange.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet {

namespace nlsr {

void NeighborStateDown::processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event)
{
    if (event == Neighbor::HELLO_DATA_RECEIVED) {  // After receive hello data, neighbor changed to ACTIVE, and exchange LSA info.
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
        neighbor->sendSyncInterestPacket();
        changeState(neighbor, new NeighborStateExchange, this);
        messageHandler->startTimer(neighbor->getSyncTimer(), neighbor->getSyncInterval());
    }
    else if (event == Neighbor::SYNC_RECEIVED) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getSyncTimer());
        messageHandler->startTimer(neighbor->getSyncTimer(), neighbor->getSyncInterval());
    }
}

} // namespace nlsr

} // namespace inet


