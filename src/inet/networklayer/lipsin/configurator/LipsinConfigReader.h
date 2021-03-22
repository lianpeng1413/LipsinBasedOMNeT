/*
 * LipsinConfigReader.h
 *
 *  Created on: Mar 15, 2021
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_LIPSIN_CONFIGURATOR_LIPSINCONFIGREADER_H_
#define INET_NETWORKLAYER_LIPSIN_CONFIGURATOR_LIPSINCONFIGREADER_H_

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/lipsin/LipsinLdEntry.h"
#include "inet/networklayer/lipsin/LipsinLdTable.h"

namespace inet {
namespace lipsin{
class INET_API LipsinConfigReader {
private:
    cModule *lipsinModule = nullptr;
    IInterfaceTable *ift = nullptr;
    LipsinLdTable *plt = nullptr, *dlt = nullptr, *vlt = nullptr;
    simtime_t deletePeriod;

private:
    cPar& par(const char *name) const { return lipsinModule->par(name); }
    int getIntAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    bool getBoolAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    const char *getStrAttrOrPar(const cXMLElement& ifConfig, const char *name) const;

    /**
         * Search an InterfaceEntry in IInterfaceTable by interface name or toward module name
         * an returns the InterfaceEntry pointer or throws an error.
         */
    std::vector<InterfaceEntry *> getInterfaceByXMLAttributesOf(const cXMLElement& ifConfig);
    cXMLElement * findMatchingPhyLinkConfig(const cXMLElementList& linksConfig, const InterfaceEntry& intf);

    /**
     * Loads OSPF configuration information for a router interface.
     * Handles POINTTOPOINT, BROADCAST, NBMA and POINTTOMULTIPOINT interfaces.
     */
    void loadPhyInterfaceParameters(const cXMLElement& linkConfig, InterfaceEntry& ie);
    void loadVirInterfaceParameters(const cXMLElement& linkConfig, InterfaceEntry& ie);
public:
    LipsinConfigReader(cModule *lipsinModule, IInterfaceTable *ift,LipsinLdTable *plt,LipsinLdTable *dlt, LipsinLdTable *vlt,simtime_t dp):lipsinModule(lipsinModule),ift(ift),plt(plt),dlt(dlt),vlt(vlt),deletePeriod(dp){}
    virtual ~LipsinConfigReader();
    bool loadConfigFromXML(cXMLElement *linksConfig);
};
}// namespace lipsin
} /* namespace inet */

#endif /* INET_NETWORKLAYER_LIPSIN_CONFIGURATOR_LIPSINCONFIGREADER_H_ */
