/*
 * NlsrNeighborStateFull.h
 *
 *  Created on: Sep 26, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEFULL_H_
#define INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEFULL_H_

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborState.h"

namespace inet {

namespace nlsr {

class INET_API NeighborStateFull : public NeighborState
{
  public:
    virtual void processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event) override;
    virtual Neighbor::NeighborStateType getState() const override { return Neighbor::FULL_STATE; }
};

} // namespace ospfv2

} // namespace inet




#endif /* INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEFULL_H_ */
