/*
 * NlsrNeighborState.h
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATE_H_
#define INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATE_H_


#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"

namespace inet {

namespace nlsr {

class INET_API NeighborState
{
  protected:
    void changeState(Neighbor *neighbor, NeighborState *newState, NeighborState *currentState);
    bool hasLsaUpdate(Neighbor *neighbor);

  public:
    virtual ~NeighborState() {}

    virtual void processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event) = 0;
    virtual Neighbor::NeighborStateType getState() const = 0;
};

} // namespace nlsr

} // namespace inet



#endif /* INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATE_H_ */
