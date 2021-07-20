/*
 * NlsrNeighborStateExchange.cc
 *
 *  Created on: Sep 25, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborStateDown.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborStateExchange.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborStateFull.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet {

namespace nlsr {

void NeighborStateExchange::processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event)
{
    if ((event == Neighbor::KILL_NEIGHBOR) || (event == Neighbor::LINK_DOWN)) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        neighbor->reset();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        changeState(neighbor, new NeighborStateDown, this);
    }
    else if (event == Neighbor::INACTIVITY_TIMER) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        neighbor->reset();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        changeState(neighbor, new NeighborStateDown, this);
    }
    else if (event == Neighbor::HELLO_DATA_RECEIVED) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
        changeState(neighbor, new NeighborStateDown, this);
    }
    else if (event == Neighbor::SYNC_TIMER) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getSyncTimer());
        neighbor->sendSyncInterestPacket();
        messageHandler->startTimer(neighbor->getSyncTimer(), neighbor->getSyncInterval());
    }
    else if (event == Neighbor::SYNC_RECEIVED) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getSyncTimer());
        messageHandler->startTimer(neighbor->getSyncTimer(), neighbor->getSyncInterval());
    }
    // lsdb sync finished/
    else if (event == Neighbor::EXCHANGE_DONE) {
        if (neighbor->getInterface()->getWhetherFull()) {
//            MessageHandler *messageHandler = neighbor->getInterface()->getRouter()->getMessageHandler();
            changeState(neighbor, new NeighborStateFull, this);
        }

    }
}

} // namespace nlsr

} // namespace inet




