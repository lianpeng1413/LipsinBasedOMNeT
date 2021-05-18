/*
 * LipsinTopoManager.cc
 *
 *  Created on: Apr 13, 2021
 *      Author: root
 */

#include "inet/applications/generic/LipsinRoute/LipsinTopoManager.h"
#include "inet/common/PatternMatcher.h"
#include "inet/common/XMLUtils.h"
#include <regex>

namespace inet {
namespace lipsin{
const char *LipsinTopoManager::getStrAttr(const cXMLElement& ifConfig, const char *name) const
{
    const char *attrStr = ifConfig.getAttribute(name);
    if (attrStr && *attrStr)
        return attrStr;
    else{
        cRuntimeError("Unknown %s at %s",
                name,ifConfig.getSourceLocation());
        return nullptr;
    }

}
void LipsinTopoManager::loadDisConnectParameters(const cXMLElement& timeConfig,simtime_t &t)
{
    const char * src = getStrAttr(timeConfig,"src-module");
    const char * dest = getStrAttr(timeConfig,"dest-module");
    std::string srcString(src),destString(dest);
    std::smatch match_src,match_dest;
    std::regex r("LEO([0-9]+)");
    std::regex_search(srcString,match_src,r);
    std::regex_search(destString,match_dest,r);
    int srcId,destId;
    srcId = std::stoi(match_src.str(1));
    destId = std::stoi(match_dest.str(1));
    changeVector.push_back(TopoChangeInfo(t,srcId,destId,false));
}
void LipsinTopoManager::loadConnectParameters(const cXMLElement& timeConfig,simtime_t &t)
{
    const char * src = getStrAttr(timeConfig,"src-module");
    const char * dest = getStrAttr(timeConfig,"dest-module");
    std::string srcString(src),destString(dest);
    std::smatch match_src,match_dest;
    std::regex r("LEO([0-9]+)");
    std::regex_search(srcString,match_src,r);
    std::regex_search(destString,match_dest,r);
    int srcId,destId;
    srcId = std::stoi(match_src.str(1));
    destId = std::stoi(match_dest.str(1));
    changeVector.push_back(TopoChangeInfo(t,srcId,destId,true));
}
bool LipsinTopoManager::loadConfigFromXML(cXMLElement *topoChangeConfig){
    if(strcmp(topoChangeConfig->getTagName(), "script"))
        throw cRuntimeError("Cannot read LIPSIN configuration, unexpected element '%s' at %s", topoChangeConfig->getTagName(), topoChangeConfig->getSourceLocation());
    cXMLElementList ats = topoChangeConfig->getElementsByTagName("At");
    for(auto & at : ats){
        cXMLElementList timeConfigs = at->getChildren();
        const char *tAttr = at->getAttribute("t");
        simtime_t t = SimTime::parse(tAttr);
        for (auto & timeConfig : timeConfigs) {
            std::string nodeName = timeConfig->getTagName();
            if ((nodeName == "disconnect"))
                loadDisConnectParameters(*timeConfig,t);
            else if((nodeName == "connect"))
                loadConnectParameters(*timeConfig,t);
        }
    }
    scheduleTopoChange();
    return true;
}
bool LipsinTopoManager::changeTopo(){
    simtime_t now = simTime();
    if(index==changeVector.size()) return false;
    for(index;index<changeVector.size();index++){
        if(now >= changeVector[index].getTime()){
            if(changeVector[index].getStatus()){
                table->changeLinkUp(changeVector[index].getSrc(), changeVector[index].getDest());
                table->changeLinkUp(changeVector[index].getDest(), changeVector[index].getSrc());
            }
            else{
                table->changeLinkDown(changeVector[index].getSrc(), changeVector[index].getDest());
                table->changeLinkDown(changeVector[index].getDest(), changeVector[index].getSrc());
            }
//            std::cout<<"Successful change the state at "<<now<<",src:"<<changeVector[index].getSrc()<<",dest:"<<
//                    changeVector[index].getDest()<<" "<< changeVector[index].getStatus() << std::endl;
        }else break;
    }
//    table->reCalculateSPFP(linkSetById);
    table->reCalculateSPF(linkSetById);
    return true;

}
bool LipsinTopoManager::scheduleTopoChange(){
    simtime_t tmp;
    for(int i=0;i<changeVector.size();i++){
        if(tmp != changeVector[i].getTime()){
            tmp = changeVector[i].getTime();
            cMessage *msg = new cMessage("updateTimer");
            module->scheduleAt(tmp, msg);
        }
    }
    return true;
}
}
} /* namespace inet */
