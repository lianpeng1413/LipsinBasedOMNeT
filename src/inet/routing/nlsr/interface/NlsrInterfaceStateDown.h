/*
 * NlsrInterfaceStateDown.h
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATEDOWN_H_
#define INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATEDOWN_H_

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/interface/NlsrInterfaceState.h"

namespace inet {

namespace nlsr {

class INET_API InterfaceStateDown : public NlsrInterfaceState
{
  public:
    virtual void processEvent(NlsrInterface *intf, NlsrInterface::NlsrInterfaceEventType event) override;
    virtual NlsrInterface::NlsrInterfaceStateType getState() const override { return NlsrInterface::DOWN_STATE; }
};

} // namespace nlsr

} // namespace inet



#endif /* INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATEDOWN_H_ */
