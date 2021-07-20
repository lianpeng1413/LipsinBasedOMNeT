/*
 * NlsrNeighborStateChange.h
 *
 *  Created on: Sep 25, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEEXCHANGE_H_
#define INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEEXCHANGE_H_

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/interface/NlsrInterfaceState.h"

namespace inet{
namespace nlsr{

class INET_API NeighborStateExchange : public NeighborState
{
  public:
    virtual void processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event) override;
    virtual Neighbor::NeighborStateType getState() const override { return Neighbor::EXCHANGE_STATE; }
};

} // namespace Nlsr

} // namespace inet



#endif /* INET_ROUTING_NLSR_NEIGHBOR_NLSRNEIGHBORSTATEEXCHANGE_H_ */
