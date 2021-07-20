/*
 * LSAHandler.h
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_MESSAGEHANDLER_LSAHANDLER_H_
#define INET_ROUTING_NLSR_MESSAGEHANDLER_LSAHANDLER_H_

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/messageHandler/IMessageHandler.h"

namespace inet {
namespace nlsr {

class INET_API LSAHandler : public IMessageHandler
{
private:
    simtime_t m_lsaRefreshTime;
    std::vector<iName> pendingSyncAdjLsaName;
    std::vector<iName> pendingSyncNameLsaName;
    std::vector<NlsrAdjLsa *> pendingSyncAdjLsa;
    std::vector<NlsrNameLsa *> pendingSyncNameLsa;

  public:
    LSAHandler(Router *containingRouter);

    void processPacket(Packet *pk, NlsrInterface *intf, Neighbor *neighbor);

    /* Finds and sends a requested name LSA. */
    void processInterestForNameLsa(Packet *packet, NlsrInterface *intf, Neighbor *neighbor);

    /* Finds and sends a requested adj LSA. */
    void processInterestForAdjLsa(Packet *packet, NlsrInterface *intf, Neighbor *neighbor);

    /* process received name LSA data packet, and trigger LSDB update.*/
    void processContentNameLsa(Packet *dataPacket, NlsrInterface *intf, Neighbor *neighbor);

    /* process received adj LSA data packet, and trigger LSDB update.*/
    void processContentAdjLsa(Packet *dataPacket, NlsrInterface *intf, Neighbor *neighbor);
};

} // namespace NLSR

} // namespace inet




#endif /* INET_ROUTING_NLSR_MESSAGEHANDLER_LSAHANDLER_H_ */
