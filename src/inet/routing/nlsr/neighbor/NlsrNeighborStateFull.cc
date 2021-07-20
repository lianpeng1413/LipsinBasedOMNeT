/*
 * NlsrNeighborStateFull.cc
 *
 *  Created on: Sep 26, 2020
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

void NeighborStateFull::processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event)
{
    if ((event == Neighbor::KILL_NEIGHBOR) || (event == Neighbor::LINK_DOWN)) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        neighbor->reset();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        changeState(neighbor, new NeighborStateDown, this);
    }
    else if (event == Neighbor::INACTIVITY_TIMER) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        auto intf = neighbor->getInterface();
        neighbor->reset();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        changeState(neighbor, new NeighborStateDown, this);
        intf->processEvent(NlsrInterface::INTERFACE_DOWN); //changed to down, modified by yanfei 20210412

    }
    else if (event == Neighbor::HELLO_DATA_RECEIVED) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
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
    else if ((event == Neighbor::SEQUENCE_NUMBER_MISMATCH)) {
        changeState(neighbor, new NeighborStateExchange, this);
    }
}

} // namespace nlsr
} // namespace inet




