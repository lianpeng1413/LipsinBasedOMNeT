/*
 * HelloHandler.h
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_MESSAGEHANDLER_HELLOHANDLER_H_
#define INET_ROUTING_NLSR_MESSAGEHANDLER_HELLOHANDLER_H_

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/messageHandler/IMessageHandler.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"
#include "inet/routing/nlsr/neighbor/adjacencyList.h"

namespace inet {

namespace nlsr {

// hello packet interest name like: /router1/HelloINFO/router2
class INET_API HelloHandler : public IMessageHandler
{
private:
//    AdjacencyList m_adjacencyList;

public:
    HelloHandler(Router *containingRouter);

    /* Processes a Hello interest packet from a neighbor  */
    void processInterestPacket(Packet *packet, NlsrInterface *intf, Neighbor *unused);

    /* Process incoming hello data. // TODO Verify signatures
     * whenever incoming data is verified, change the status of this neighbor, and install adjLSA. */
    void processDataPacket(Packet *dataPacket, NlsrInterface *intf);

    void generateAdjLsaAndInstall(iName adjLsaName, NlsrInterface *intf);

    int getIntAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    bool getBoolAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    const char *getStrAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    bool loadConfigFromXML(cXMLElement *Config, Router *nlsrRouter);
};

} // namespace NLSR
} // namespace inet

#endif /* INET_ROUTING_NLSR_MESSAGEHANDLER_HELLOHANDLER_H_ */
