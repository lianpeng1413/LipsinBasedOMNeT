/*
 * NlsrConfigReader.h
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 *     This module used to configure node's name and interface output cost
 */

#ifndef INET_ROUTING_NDNSIM_NLSR_NLSRCONFIGREADER_H
#define INET_ROUTING_NDNSIM_NLSR_NLSRCONFIGREADER_H

#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
//#include "inet/routing/nlsr/route/ndnRoutingTable.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet {

namespace nlsr {

/**
 * Configuration reader for the nlsr module.
 */
class INET_API NlsrConfigReader
{
  private:
    cModule *nlsrModule = nullptr;
    IInterfaceTable *ift = nullptr;    // provides access to the interface table
    Router *nlsrRouter = nullptr;    // data structure to fill in

  private:
    cPar& par(const char *name) const { return nlsrModule->par(name); }
    int getIntAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    bool getBoolAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    const char *getStrAttrOrPar(const cXMLElement& ifConfig, const char *name) const;

    /**
     * Loads a list of nlsr Areas connected to this router from the config XML.
     * @param routerNode [in]  XML node describing this router.
     * @param areaList   [out] A set of nlsr Areas connected to this router.
     */
    void getAreaListFromXML(const cXMLElement& routerNode, std::set<AreaId>& areaList) const;

    /**
     * Loads basic configuration information for a given area from the config XML.
     * Reads the configured address ranges, and whether this Area should be handled as a stub Area.
     */
    void loadAreaFromXML(const cXMLElement& asConfig, AreaId areaID);

    /**
     * Search an InterfaceEntry in IInterfaceTable by interface name or toward module name
     * an returns the InterfaceEntry pointer or throws an error.
     */
    std::vector<InterfaceEntry *> getInterfaceByXMLAttributesOf(const cXMLElement& ifConfig);

    cXMLElement * findMatchingConfig(const cXMLElementList& routerConfig, const InterfaceEntry& intf);

    /**
     * Loads nlsr configuration information for a router interface.
     * Handles POINTTOPOINT and POINTTOMULTIPOINT interfaces.
     */
    void loadInterfaceParameters(const cXMLElement& ifConfig, InterfaceEntry& intf);

    /**
     * Loads the configuration of a host route (a host directly connected to the router).
     */
    void loadHostRoute(const cXMLElement& hostRouteConfig);

    /**
     * Loads the configuration of a loopback interface.
     */
    void loadLoopbackParameters(const cXMLElement& loConfig, InterfaceEntry& intf);

  public:
    NlsrConfigReader(cModule *nlsrModule, IInterfaceTable *ift);
    virtual ~NlsrConfigReader();

    /**
     * Loads the configuration of the nlsr data structure from the config XML.
     * Returns true if the configuration was successfully loaded.
     */
    bool loadConfigFromXML(cXMLElement *Config, Router *nlsrRouter);
};
}// namespace nlsr

} // namespace inet

#endif // ifndef INET_ROUTING_NDNSIM_NLSR_NLSRCONFIGREADER_H

