/*
 * NlsrInterfaceStateDown.cc
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/interface/NlsrInterfaceStateDown.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "NlsrInterfaceStatePointToPoint.h"

namespace inet {

namespace nlsr {

void InterfaceStateDown::processEvent(NlsrInterface *intf, NlsrInterface::NlsrInterfaceEventType event)
{
    if (event == NlsrInterface::INTERFACE_UP) {
        MessageHandler *messageHandler = intf->getArea()->getRouter()->getMessageHandler();
        messageHandler->startTimer(intf->getHelloTimer(), RNGCONTEXT truncnormal(0.1, 0.01));   // add some deviation to avoid startup collisions
        changeState(intf, new InterfaceStatePointToPoint, this);
    }

}

} // namespace nlsr

} // namespace inet



