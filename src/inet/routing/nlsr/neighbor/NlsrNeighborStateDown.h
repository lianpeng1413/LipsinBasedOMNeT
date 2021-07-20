/*
 * NeighborStateDown.h
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEDOWN_H_
#define INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEDOWN_H_

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighborState.h"

namespace inet {

namespace nlsr {

class INET_API NeighborStateDown : public NeighborState
{
  public:
    virtual void processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event) override;
    virtual Neighbor::NeighborStateType getState() const override { return Neighbor::DOWN_STATE; }
};

} // namespace nlsr

} // namespace inet



#endif /* INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEDOWN_H_ */
