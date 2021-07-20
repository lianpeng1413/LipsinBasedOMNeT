/*
 * NlsrNeighborState.cc
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborState.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet {
namespace nlsr {
// if there's lsdb different,
void NeighborState::changeState(Neighbor *neighbor, NeighborState *newState, NeighborState *currentState)
{
    neighbor->changeState(newState, currentState);

    if ((currentState->getState() == Neighbor::FULL_STATE) || (newState->getState() == Neighbor::FULL_STATE))
        if(hasLsaUpdate(neighbor))
            neighbor->getInterface()->getArea()->getRouter()->rebuildRoutingTable();
}

bool NeighborState::hasLsaUpdate(Neighbor *neighbor)
{
    bool shouldRebuildRoutingTable = false;
    bool differ = false;

    RouterName routerName = neighbor->getInterface()->getArea()->getRouter()->getRouterID();

    //Determine whether LSDB has difference.
    if(neighbor->getInterface()->getWhetherFull())
        shouldRebuildRoutingTable = true;
    else
        shouldRebuildRoutingTable = false;

    return shouldRebuildRoutingTable;
}

} // namespace nlsr
} // namespace inet




