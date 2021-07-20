/*
 * IMessageHandler.h
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_MESSAGEHANDLER_IMESSAGEHANDLER_H_
#define INET_ROUTING_NLSR_MESSAGEHANDLER_IMESSAGEHANDLER_H_

#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"

namespace inet {

namespace nlsr {

class Router;
class NlsrInterface;
class Neighbor;

class INET_API IMessageHandler
{
  protected:
    Router *router;

  public:
    IMessageHandler(Router *containingRouter) { router = containingRouter; }
    virtual ~IMessageHandler() {}

    void processPacket(Packet *pk, NlsrInterface *intf, Neighbor *neighbor);
};

} // namespace nlsr

} // namespace inet



#endif /* INET_ROUTING_NLSR_MESSAGEHANDLER_IMESSAGEHANDLER_H_ */
