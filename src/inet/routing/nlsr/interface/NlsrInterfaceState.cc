/*
 * NlsrInterfaceState.cc
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */

#include <map>

#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/interface/NlsrInterfaceState.h"
#include "inet/routing/nlsr/interface/NlsrInterfaceStateDown.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"

namespace inet {

namespace nlsr {

void NlsrInterfaceState::changeState(NlsrInterface *intf, NlsrInterfaceState *newState, NlsrInterfaceState *currentState)
{
    NlsrInterface::NlsrInterfaceStateType oldState = currentState->getState();
    NlsrInterface::NlsrInterfaceStateType nextState = newState->getState();
    bool shouldRebuildRoutingTable = false;

    intf->changeState(newState, currentState);

    if ((oldState == NlsrInterface::DOWN_STATE) || (nextState == NlsrInterface::DOWN_STATE)){
        // Get neighbor name, and delete adjLsa which from neighbor.
        unsigned long neighborCount = intf->getArea()->getRouter()->getNeighborNum();
        for(unsigned long i = 0; i < neighborCount; i++){
            auto *neighbor = intf->getArea()->getRouter()->getNeighbor(i);
            iName neighborName = neighbor->getNeighborName();

            //Delete local neighbor item info, which installed in adjLSA.
            NlsrAdjLsa *adjLsa = intf->getArea()->findAdjLsa(intf->getArea()->getRouter()->getRouterID());
            if(adjLsa != nullptr){
                auto m_adl = adjLsa->getM_adlForUpdate();
                m_adl->deleteNeighbor(neighborName);
                adjLsa->setM_adl(m_adl);
                shouldRebuildRoutingTable = true;
            }

            intf->removeNeighbor(neighborName);
            //Delete neighbor adjLsa and nameLsa.
            intf->getArea()->removeAdjLsa(neighborName);
//            shouldRebuildRoutingTable = true;
        }
    }

//    if (nextState == NlsrInterface::POINTTOPOINT_STATE) {
//        // when the interface state changed from down to up, the interface do not known the neighbor name
//        // broadCast this hello packet.
//        iName destination;
//        destination.set("NLSR", "ROUTERS", "MCAST");
//        intf->sendHelloInterestPacket(destination, 1);
//    }

    if(shouldRebuildRoutingTable){
        intf->getArea()->getRouter()->rebuildRoutingTable();
    }
//    intf->getArea()->getRouter()->rebuildRoutingTable();
}

} // namespace nlsr
} // namespace inet





