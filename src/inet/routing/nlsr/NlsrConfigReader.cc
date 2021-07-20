// read nlsr configuration

#include "NlsrConfigReader.h"

#include <algorithm>
#include <map>
#include <memory.h>
#include <stdlib.h>
#include <string>

#include "inet/common/ModuleAccess.h"
#include "inet/common/PatternMatcher.h"
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/NlsrConfigReader.h"
#include "inet/routing/nlsr/messageHandler/HelloHandler.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/router/NlsrArea.h"

namespace inet {
namespace nlsr {

using namespace xmlutils;

NlsrConfigReader::NlsrConfigReader(cModule *nlsrModule, IInterfaceTable *ift) :
        nlsrModule(nlsrModule), ift(ift)
{
}

NlsrConfigReader::~NlsrConfigReader()
{
}

bool NlsrConfigReader::loadConfigFromXML(cXMLElement *asConfig, Router *nlsrRouter)
{
    this->nlsrRouter = nlsrRouter;

    // get the configure file name
    if (strcmp(asConfig->getTagName(), "NLSRConfig"))
        throw cRuntimeError("Cannot read nlsr configuration, unexpected element '%s' at %s", asConfig->getTagName(), asConfig->getSourceLocation());

    cModule *myNode = findContainingNode(nlsrModule);
    ASSERT(myNode);
    std::string nodeFullPath = myNode->getFullPath();
    std::string nodeShortenedFullPath = nodeFullPath.substr(nodeFullPath.find('.') + 1);

    // load information on this router: router name, interfaceOutPut cost. " /LEOSat/Orbit/router1".
    cXMLElementList routers = asConfig->getElementsByTagName("Router");
    cXMLElement *routerNode = nullptr;
    for (auto & router : routers) {
        const char *nodeName = getMandatoryFilledAttribute(*(router), "name");
        inet::PatternMatcher pattern(nodeName, true, true, true);
        if (pattern.matches(nodeFullPath.c_str()) || pattern.matches(nodeShortenedFullPath.c_str())) {    // match Router@name and fullpath of my node
            routerNode = router;
            router->setNodeValue(nodeName); //set router name
            break;
        }
    }
    if (routerNode == nullptr) {
        throw cRuntimeError("No configuration for Router '%s' at '%s'", nodeFullPath.c_str(), asConfig->getSourceLocation());
    }

    EV_DEBUG << "NlsrConfigReader: Loading info for Router " << nodeFullPath << "\n";

    std::set<AreaId> areaList;
    getAreaListFromXML(*routerNode, areaList);
    // load area information
    for (const auto & elem : areaList) {
        loadAreaFromXML(*asConfig, elem);
    }

    cXMLElementList routerConfig = routerNode->getChildren();

    // load interface information
    for (int n = 0; n < ift->getNumInterfaces(); n++) {
        InterfaceEntry *intf = ift->getInterface(n);
        cXMLElement *ifConfig = findMatchingConfig(routerConfig, *intf);
        if(ifConfig) {
            if(intf->isLoopback())
                loadLoopbackParameters(*ifConfig, *intf);
            else
                loadInterfaceParameters(*ifConfig, *intf);
        }
    }

    // load remaining information
    for (auto & elem : routerConfig) {
        std::string nodeName = elem->getTagName();
        if ((nodeName == "PointToPointInterface") || (nodeName == "PointToMultiPointInterface")) {
            continue;
        }
        else if (nodeName == "HostInterface") {
            loadHostRoute(*elem);
        }
        else {
            throw cRuntimeError("Invalid '%s' node in Router '%s' at %s",
                    nodeName.c_str(), nodeFullPath.c_str(), elem->getSourceLocation());
        }
    }

    return true;
}

void NlsrConfigReader::getAreaListFromXML(const cXMLElement& routerNode, std::set<AreaId>& areaList) const
{
    cXMLElementList routerConfig = routerNode.getChildren();
    for (auto & elem : routerConfig) {
        std::string nodeName = (elem)->getTagName();
        if ((nodeName == "PointToPointInterface") ||
            (nodeName == "PointToMultiPointInterface"))
        {
            AreaId areaID = 0;
            if (areaList.find(areaID) == areaList.end())
                areaList.insert(areaID);
        }
    }
}

void NlsrConfigReader::loadAreaFromXML(const cXMLElement& asConfig, AreaId areaID)
{
    std::string areaXPath("Area[@id='");
    areaXPath += std::to_string(areaID);
    areaXPath += "']";

    cXMLElement *areaConfig = asConfig.getElementByPath(areaXPath.c_str());
    if (areaConfig == nullptr) {
        if(areaID != 0 )
            throw cRuntimeError("No configuration for Area ID: %s at %s", std::to_string(areaID).c_str(), asConfig.getSourceLocation());
        NlsrArea *area = new NlsrArea(ift, areaID);
        area->addWatches();
        nlsrRouter->addArea(area);
        return;
    }

    EV_DEBUG << "    loading info for Area id = " << std::to_string(areaID) << "\n";

    NlsrArea *area = new NlsrArea(ift, areaID);
    area->addWatches();
    cXMLElementList areaDetails = areaConfig->getChildren();
    for (auto & areaDetail : areaDetails) {
        std::string nodeName = (areaDetail)->getTagName();
        if (nodeName == "Stub") {
            if (areaID == BACKBONE_AREAID)
                throw cRuntimeError("The backbone cannot be configured as a stub at %s", (areaDetail)->getSourceLocation());
            area->setStubDefaultCost(atoi(getMandatoryFilledAttribute(*areaDetail, "defaultCost")));
        }
        else
            throw cRuntimeError("Invalid node '%s' at %s", nodeName.c_str(), (areaDetail)->getSourceLocation());
    }
    // Add the Area to the router
    nlsrRouter->addArea(area);
}

void NlsrConfigReader::loadHostRoute(const cXMLElement& hostRouteConfig)
{
    std::string intfModeStr = getStrAttrOrPar(hostRouteConfig, "interfaceMode");
    if(intfModeStr == "NoNLSR")
        return;

    HostRouteParameters hostParameters;
    AreaId hostArea = 0;

    for(auto &ie : getInterfaceByXMLAttributesOf(hostRouteConfig)) {
        int ifIndex = ie->getInterfaceId();
        hostParameters.ifIndex = ifIndex;
        EV_DEBUG << "        loading HostInterface " << ie->getInterfaceName() << " ifIndex[" << ifIndex << "]\n";
        hostParameters.linkCost = getIntAttrOrPar(hostRouteConfig, "linkCost");

        // add the host route to the NLSR data structure.
        NlsrArea *area = nlsrRouter->getAreaByID(hostArea);
        if (area != nullptr) {
            area->addHostRoute(hostParameters);
        }
        else {
            throw cRuntimeError("Loading HostInterface '%s' aborted, unknown area %s at %s", ie->getInterfaceName(), std::to_string(hostArea).c_str(), hostRouteConfig.getSourceLocation());
        }
    }
}

cXMLElement * NlsrConfigReader::findMatchingConfig(const cXMLElementList& routerConfig, const InterfaceEntry& intf)
{
    for (auto & ifConfig : routerConfig) {
        std::string nodeName = ifConfig->getTagName();
        if ((nodeName == "PointToPointInterface") || (nodeName == "PointToMultiPointInterface")) {
            const char *ifName = (*ifConfig).getAttribute("ifName");
            if (ifName && *ifName) {
                inet::PatternMatcher pattern(ifName, true, true, true);
                if (pattern.matches(intf.getFullName()) ||
                        pattern.matches(intf.getInterfaceFullPath().c_str()) ||
                        pattern.matches(intf.getInterfaceName())) {
                    return ifConfig;
                }

                continue;
            }

            const char *toward = getMandatoryFilledAttribute(*ifConfig, "toward");
            cModule *destnode = getSimulation()->getSystemModule()->getModuleByPath(toward);
            if (!destnode)
                throw cRuntimeError("toward module `%s' not found at %s", toward, (*ifConfig).getSourceLocation());

            int gateId = intf.getNodeOutputGateId();
            if ((gateId != -1) && ift->getHostModule()->gate(gateId)->pathContains(destnode))
                return ifConfig;
        }
    }

    return nullptr;
}

/**
 *  Used to configure interface output cost. Interface state changed to up.
 */
void NlsrConfigReader::loadInterfaceParameters(const cXMLElement& ifConfig, InterfaceEntry& ie)
{
    std::string intfModeStr = getStrAttrOrPar(ifConfig, "interfaceMode");
    if(intfModeStr == "Nonlsr")
        return;

    std::string interfaceType = ifConfig.getTagName();
    int ifIndex = ie.getInterfaceId();
    std::string ifName = ie.getInterfaceName();

    EV_DEBUG << "        loading " << interfaceType << " " << ifName << " (ifIndex=" << ifIndex << ")\n";

    NlsrInterface *intf = new NlsrInterface;

    intf->setInterfaceName(ifName);
    AreaId areaID = 0;
    intf->setAreaId(areaID);
    intf->setIfIndex(ift, ifIndex);

    if (interfaceType == "PointToPointInterface")
        intf->setType(NlsrInterface::POINTTOPOINT);
    else if (interfaceType == "PointToMultiPointInterface")
        intf->setType(NlsrInterface::POINTTOMULTIPOINT);
    else {
        delete intf;
        throw cRuntimeError("Unknown interface type '%s' for interface %s (ifIndex=%d) at %s",
                interfaceType.c_str(), ifName.c_str(), ifIndex, ifConfig.getSourceLocation());
    }

    if(intfModeStr == "ACTIVE")
        intf->setMode(NlsrInterface::ACTIVE);
    else if(intfModeStr == "PASSIVE")
        intf->setMode(NlsrInterface::PASSIVE);
    else {
        delete intf;
        throw cRuntimeError("Unknown interface mode '%s' for interface %s (ifIndex=%d) at %s",
                interfaceType.c_str(), ifName.c_str(), ifIndex, ifConfig.getSourceLocation());
    }

    Metric cost = getIntAttrOrPar(ifConfig, "interfaceOutputCost");
    if(cost == 0)
        intf->setOutputCost(round(par("referenceBandwidth").intValue() / ie.getDatarate()));
    else
        intf->setOutputCost(cost);

    intf->setHelloInterval(getIntAttrOrPar(ifConfig, "helloInterval"));
    intf->setRouterDeadInterval(getIntAttrOrPar(ifConfig, "routerDeadInterval"));

    // add the interface to it's Area
    NlsrArea *area = nlsrRouter->getAreaByID(areaID);
    if (area != nullptr) {
        area->addInterface(intf);
        intf->processEvent(NlsrInterface::INTERFACE_UP);    // notification should come from the blackboard...
    }
    else {
        delete intf;
        throw cRuntimeError("Loading %s ifIndex[%d] in Area %s aborted at %s", interfaceType.c_str(), ifIndex, std::to_string(areaID).c_str(), ifConfig.getSourceLocation());
    }
}

void NlsrConfigReader::loadLoopbackParameters(const cXMLElement& loConfig, InterfaceEntry& ie)
{
    int ifIndex = ie.getInterfaceId();
    // Loopbacks are considered host routes in NLSR,
    HostRouteParameters hostParameters;
    hostParameters.ifIndex = ifIndex;
    hostParameters.linkCost = getIntAttrOrPar(loConfig, "linkCost");
    AreaId hostArea = 0;
    // add the host route to the NLSR data structure.
    NlsrArea *area = nlsrRouter->getAreaByID(hostArea);
    if (area != nullptr)
        area->addHostRoute(hostParameters);
    else
        throw cRuntimeError("Loading LoopbackInterface '%s' aborted, unknown area %s at %s", ie.getInterfaceName(), std::to_string(hostArea).c_str(), loConfig.getSourceLocation());
}

std::vector<InterfaceEntry *> NlsrConfigReader::getInterfaceByXMLAttributesOf(const cXMLElement& ifConfig)
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
    }

    const char *toward = getMandatoryFilledAttribute(ifConfig, "toward");
    cModule *destnode = getSimulation()->getSystemModule()->getModuleByPath(toward);
    if (!destnode)
        throw cRuntimeError("'ifName' or 'toward' module `%s' not found at %s", toward, ifConfig.getSourceLocation());

    cModule *host = ift->getHostModule();
    for (int i = 0; i < ift->getNumInterfaces(); i++) {
        InterfaceEntry *ie = ift->getInterface(i);
        if (ie) {
            int gateId = ie->getNodeOutputGateId();
            if ((gateId != -1) && (host->gate(gateId)->pathContains(destnode))) {
                results.push_back(ie);
                return results;
            }
        }
    }
    throw cRuntimeError("Error reading XML config: IInterfaceTable contains no interface toward '%s' at %s", toward, ifConfig.getSourceLocation());
}

int NlsrConfigReader::getIntAttrOrPar(const cXMLElement& ifConfig, const char *name) const
{
    const char *attrStr = ifConfig.getAttribute(name);
    if (attrStr && *attrStr)
        return atoi(attrStr);
    return par(name);
}

const char *NlsrConfigReader::getStrAttrOrPar(const cXMLElement& ifConfig, const char *name) const
{
    const char *attrStr = ifConfig.getAttribute(name);
    if (attrStr && *attrStr)
        return attrStr;
    return par(name);
}

} // namespace nlsr
} // namespace inet

