/*
 * NlsrInterfaceStateUp.cc
 *
 *  Created on: Sep 25, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/interface/NlsrInterfaceStateDown.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "NlsrInterfaceStatePointToPoint.h"

namespace inet {
namespace nlsr {

void InterfaceStatePointToPoint::processEvent(NlsrInterface *intf, NlsrInterface::NlsrInterfaceEventType event)
{
    if (event == NlsrInterface::INTERFACE_DOWN) {
        intf->reset();
        changeState(intf, new InterfaceStateDown, this);
    }

    else if (event == NlsrInterface::HELLO_TIMER) {
        unsigned long neighborCount = intf->getNeighborCount();
        if (intf->getType() == NlsrInterface::POINTTOMULTIPOINT && neighborCount > 0) {
            int ttl = 1;
            for (unsigned long i = 0; i < neighborCount; i++) {
                intf->sendHelloInterestPacket(intf->getNeighbor(i)->getNeighborName(), ttl);
            }
        }
        else {    // NlsrInterface::broadcast. use case: wireless scenario
            iName destination;
            destination.set("NLSR", "ROUTERS", "MULTICAST");
            intf->sendHelloInterestPacket(destination, 1);
        }
        intf->getArea()->getRouter()->getMessageHandler()->startTimer(intf->getHelloTimer(), intf->getHelloInterval());
    }
}

} // namespace nlsr
} // namespace inet


