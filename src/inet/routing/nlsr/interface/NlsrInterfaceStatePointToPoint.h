/*
 * NlsrInterfaceStateUp.h
 *
 *  Created on: Sep 25, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATEPOINTTOPOINT_H_
#define INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATEPOINTTOPOINT_H_


#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/interface/NlsrInterfaceState.h"

namespace inet {

namespace nlsr {

class INET_API InterfaceStatePointToPoint : public NlsrInterfaceState
{
  public:
    virtual void processEvent(NlsrInterface *intf, NlsrInterface::NlsrInterfaceEventType event) override;
    virtual NlsrInterface::NlsrInterfaceStateType getState() const override { return NlsrInterface::POINTTOPOINT_STATE; }
};

} // namespace nlsr

} // namespace inet



#endif /* INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATEPOINTTOPOINT_H_ */
