/*
 * NlsrInterfaceState.h
 *
 *  Created on: Aug 26, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATE_H_
#define INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATE_H_

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"

namespace inet {

namespace nlsr {

class INET_API NlsrInterfaceState
{
protected:
    void changeState(NlsrInterface *intf, NlsrInterfaceState *newState, NlsrInterfaceState *currentState);

public:
    virtual ~NlsrInterfaceState() {}

    virtual void processEvent(NlsrInterface *intf, NlsrInterface::NlsrInterfaceEventType event) = 0;
    virtual NlsrInterface::NlsrInterfaceStateType getState() const = 0;
};

} // namespace nlsr

} // namespace inet



#endif /* INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACESTATE_H_ */
