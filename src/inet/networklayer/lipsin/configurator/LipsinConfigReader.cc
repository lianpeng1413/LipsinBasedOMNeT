/*
 * LipsinConfigReader.cc
 *
 *  Created on: Mar 15, 2021
 *      Author: root
 */
#include "inet/common/ModuleAccess.h"
#include "inet/common/PatternMatcher.h"
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/lipsin/LipsinLdEntry.h"
#include "inet/networklayer/lipsin/LipsinLdTable.h"
#include "inet/networklayer/lipsin/configurator/LipsinConfigReader.h"

namespace inet {
namespace lipsin {

using namespace xmlutils;

int LipsinConfigReader::getIntAttrOrPar(const cXMLElement& ifConfig, const char *name) const
{
    const char *attrStr = ifConfig.getAttribute(name);
    if (attrStr && *attrStr)
        return atoi(attrStr);
    return par(name);
}

bool LipsinConfigReader::getBoolAttrOrPar(const cXMLElement& ifConfig, const char *name) const
{
    const char *attrStr = ifConfig.getAttribute(name);
    if (attrStr && *attrStr) {
        if (strcmp(attrStr, "true") == 0 || strcmp(attrStr, "1") == 0)
            return true;
        if (strcmp(attrStr, "false") == 0 || strcmp(attrStr, "0") == 0)
            return false;
        throw cRuntimeError("Invalid boolean attribute %s = '%s' at %s", name, attrStr, ifConfig.getSourceLocation());
    }
    return par(name);
}

const char *LipsinConfigReader::getStrAttrOrPar(const cXMLElement& ifConfig, const char *name) const
{
    const char *attrStr = ifConfig.getAttribute(name);
    if (attrStr && *attrStr)
        return attrStr;
    return par(name);
}

std::vector<InterfaceEntry *> LipsinConfigReader::getInterfaceByXMLAttributesOf(const cXMLElement& ifConfig)
{
    std::vector<InterfaceEntry *> results;
    const char *ifName = ifConfig.getAttribute("ifName");
    if (ifName && *ifName) {
        inet::PatternMatcher pattern(ifName, true, true, true);
        for (int n = 0; n < ift->getNumInterfaces(); n++) {
            InterfaceEntry *intf = ift->getInterface(n);
            if (pattern.matches(intf->getFullName()) ||
                    pattern.matches(intf->getInterfaceFullPath().c_str()) ||
                    pattern.matches(intf->getInterfaceName())) {
                results.push_back(intf);
            }
        }
        return results;
    }else
        throw cRuntimeError("'ifName' not found at %s", ifConfig.getSourceLocation());
}

cXMLElement * LipsinConfigReader::findMatchingPhyLinkConfig(const cXMLElementList& linksConfig, const InterfaceEntry& intf)
{
    //find the exact linkConfig which intf == intf
    for (auto & linkConfig : linksConfig) {
        std::string nodeName = linkConfig->getTagName();
        if ((nodeName == "linkInterface"))
        {
            const char *ifName = (*linkConfig).getAttribute("ifName");
            if (ifName && *ifName) {
                inet::PatternMatcher pattern(ifName, true, true, true);
                if (pattern.matches(intf.getFullName()) ||
                        pattern.matches(intf.getInterfaceFullPath().c_str()) ||
                        pattern.matches(intf.getInterfaceName())) {
                    return linkConfig;
                }

                continue;
            }
        }
    }
    return nullptr;
}
void LipsinConfigReader::loadPhyInterfaceParameters(const cXMLElement& linkConfig, InterfaceEntry& ie)
{
    std::string ifName = ie.getInterfaceName();
    int ifIndex = ie.getInterfaceId();
    EV_INFO << " loading " << ifName << " (ifIndex=" << ifIndex << " )\n";
    int srcId = getIntAttrOrPar(linkConfig,"srcId"),
            destId = getIntAttrOrPar(linkConfig,"destId"),
            cost = getIntAttrOrPar(linkConfig,"cost"),
            linkId = getIntAttrOrPar(linkConfig,"linkId");
    if(srcId < 0 || destId < 0 || cost < 0)
        cRuntimeError("Unknown linkInterface set for interface %s (ifIndex=%d) at %s",
                        ifName.c_str(), ifIndex, linkConfig.getSourceLocation());
    if(ie.isUp()){
        LipsinLdEntry *entry = new LipsinLdEntry(&ie,plt,srcId,destId,linkId,cost);
        plt->addEntry(entry);
    }else{
        LipsinLdEntry *entry = new LipsinLdEntry(&ie,plt,srcId,destId,linkId,cost);
        plt->addEntry(entry);
        dlt->addEntry(entry);
    }
}
void LipsinConfigReader::loadVirInterfaceParameters(const cXMLElement& linkConfig, InterfaceEntry& ie)
{
    std::string ifName = ie.getInterfaceName();
    int ifIndex = ie.getInterfaceId();
    EV_INFO << " loading " << ifName << " (ifIndex=" << ifIndex << " )\n";
    int srcId = getIntAttrOrPar(linkConfig,"srcId"),
            destId = getIntAttrOrPar(linkConfig,"destId"),
            cost = getIntAttrOrPar(linkConfig,"cost"),
            linkId = getIntAttrOrPar(linkConfig,"linkId");
    if(srcId < 0 || destId < 0 || cost < 0)
        cRuntimeError("Unknown linkInterface set for interface %s (ifIndex=%d) at %s",
                        ifName.c_str(), ifIndex, linkConfig.getSourceLocation());
    if(ie.isUp()){
        LipsinLdEntry *entry = new LipsinLdEntry(&ie,vlt,srcId,destId,linkId,cost);
        vlt->addEntry(entry);
    }else{
        LipsinLdEntry *entry = new LipsinLdEntry(&ie,vlt,srcId,destId,linkId,cost);
        vlt->addEntry(entry);
        dlt->addEntry(entry);
    }
}
bool LipsinConfigReader::loadConfigFromXML(cXMLElement *linksConfig)
{
    if(strcmp(linksConfig->getTagName(), "LIPSINConfig"))
        throw cRuntimeError("Cannot read LIPSIN configuration, unexpected element '%s' at %s", linksConfig->getTagName(), linksConfig->getSourceLocation());
    cModule *myNode = findContainingNode(lipsinModule);
    ASSERT(myNode);
    std::string nodeFullPath = myNode->getFullPath();
    std::string nodeShortenedFullPath = nodeFullPath.substr(nodeFullPath.find('.') + 1);
    cXMLElementList routers = linksConfig->getElementsByTagName("Router");
    cXMLElement *routerNode = nullptr;
    for(auto & router : routers){
        const char *nodeName = getMandatoryFilledAttribute(*(router), "name");
        inet::PatternMatcher pattern(nodeName, true, true, true);
        if (pattern.matches(nodeFullPath.c_str()) || pattern.matches(nodeShortenedFullPath.c_str())) {    // match Router@name and fullpath of my node
            routerNode = router;
            break;
        }
    }
    if (routerNode == nullptr) {
        throw cRuntimeError("No configuration for Router '%s' at '%s'", nodeFullPath.c_str(), linksConfig->getSourceLocation());
    }
    EV_DEBUG << "LIPSINConfigReader: Loading info for Router " << nodeFullPath << "\n";
    cXMLElementList routerConfig = routerNode->getChildren();

    for (auto & linkConfig : routerConfig) {
        std::string nodeName = linkConfig->getTagName();
        if ((nodeName == "PhysicalLink"))
        {
            const char *ifName = (*linkConfig).getAttribute("ifName");
            if(ifName && *ifName) {
                if(InterfaceEntry *ifEntry = ift->findInterfaceByName(ifName)){
                    ifEntry->setDeletePeriod(deletePeriod);
                    loadPhyInterfaceParameters(*linkConfig,*ifEntry);
                }
            }
        }else if((nodeName == "VirtualLink")){
            const char *ifName = (*linkConfig).getAttribute("ifName");
            if(ifName && *ifName) {
                if(InterfaceEntry *ifEntry = ift->findInterfaceByName(ifName)){
                    loadVirInterfaceParameters(*linkConfig,*ifEntry);
                }
            }
        }
    }

    return true;
}

LipsinConfigReader::~LipsinConfigReader() {
    // TODO Auto-generated destructor stub
}
} /* namespace lipsin */
} /* namespace inet */
