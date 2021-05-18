/*
 * LipsinRouteConfigurator.cc
 *
 *  Created on: Apr 12, 2021
 *      Author: root
 */
#include "inet/common/ModuleAccess.h"
#include "inet/common/PatternMatcher.h"
#include "inet/common/XMLUtils.h"
#include <vector>
#include <map>
#include <regex>
#include "inet/applications/generic/LipsinRoute/LipsinRouteConfigurator.h"

namespace inet {
namespace lipsin {
using namespace xmlutils;

void LinkInfoTable::addLinkInfo(int src,int dest,int linkId,int cost,bool state,bool interOrbitType,std::vector<int> &virlist){
    LinkInfo *newLink = new LinkInfo(src,dest,linkId,cost,state,interOrbitType,virlist);
    std::pair<int,int> p(src,dest);
    if(map.find(p) == map.end())
        map[p] = newLink;
    else
        throw cRuntimeError("the link exists already from %d to %d", src, dest);
    if(linkVectorFromSrc.find(src)==linkVectorFromSrc.end()){
        std::vector<LinkInfo *> *tmp = new std::vector<LinkInfo *>();
        tmp->push_back(newLink);
        linkVectorFromSrc[src] = tmp;
    }else
        linkVectorFromSrc[src]->push_back(newLink);
    if(mapById.find(linkId)==mapById.end()){
        mapById[linkId] = newLink;
    }else
        throw cRuntimeError("the linkID %d exists already from %d to %d",linkId, src, dest);
//    std::cout<<"add link src"<<src<<" dest"<<dest<<" linkId"<<linkId<<" cost"<<cost<<" interOrbitType"<<interOrbitType<<" ";
//    for(const auto virlink:virlist){
//        std::cout<<virlink<<" ";
//    }
//    std::cout<<std::endl;
}
void LinkInfoTable::changeLinkCost(int src,int dest,int cost){
    std::pair<int,int> p(src,dest);
    if(map.find(p) == map.end())
        throw cRuntimeError("the link doesn't exist from %d to %d", src, dest);
    map[p]->setLinkCost(cost);
}
void LinkInfoTable::changeLinkDown(int src,int dest){
    std::pair<int,int> p(src,dest);
    if(map.find(p) == map.end())
        throw cRuntimeError("the link doesn't exist from %d to %d", src, dest);
    map[p]->setLinkDown();
}
void LinkInfoTable::changeLinkUp(int src,int dest){
    std::pair<int,int> p(src,dest);
    if(map.find(p) == map.end())
        throw cRuntimeError("the link doesn't exist from %d to %d", src, dest);
    map[p]->setLinkUp();
}
LinkInfoTable::LinkInfoTable(cModule *module):genModule(module){
    std::string nodeFullPath = genModule->getFullPath();
    std::smatch match;
    std::regex r("([[:w:]]+).LEO([0-9]+).([[:w:]]+)");
    bool found = regex_search(nodeFullPath,match,r);
    leoId = std::stoi(match.str(2));
}
LinkInfoTable::~LinkInfoTable(){
    for(auto links :linkVectorFromSrc){
        for(auto link : *links.second) delete link;
        links.second->clear();
        delete links.second;
    }
    map.clear();
    linkVectorFromSrc.clear();
}
std::list<std::tuple<int,int,std::list<int>*,std::list<int>*>*>::iterator LinkInfoTable::searchNearestSPFP(std::list<std::tuple<int,int,std::list<int>*,std::list<int>*>*> &unVisitedNodes){
    int minDis = INT_MAX;
    std::list<std::tuple<int,int,std::list<int>*,std::list<int>*>*>::iterator iter,nearest=unVisitedNodes.end();
    for(iter=unVisitedNodes.begin();iter!=unVisitedNodes.end();iter++){
        auto &unVisitedNodeTpl = *iter;
        if(std::get<1>(*unVisitedNodeTpl) < minDis){
            minDis = std::get<1>(*unVisitedNodeTpl);
            nearest = iter;
        }
    }
    return nearest;
}
std::list<std::tuple<int,int,std::list<int>*>*>::iterator LinkInfoTable::searchNearest(std::list<std::tuple<int,int,std::list<int>*>*> &unVisitedNodes){
    int minDis = INT_MAX;
//    std::cout<<"Size of unVisitedNodes: "<<unVisitedNodes.size()<<std::endl;
    std::list<std::tuple<int,int,std::list<int>*>*>::iterator iter,nearest=unVisitedNodes.end();
    for(iter=unVisitedNodes.begin();iter!=unVisitedNodes.end();iter++){
        auto &unVisitedNodeTpl = *iter;
        if(std::get<1>(*unVisitedNodeTpl) < minDis){
            minDis = std::get<1>(*unVisitedNodeTpl);
            nearest = iter;
        }
    }
    return nearest;
}
void LinkInfoTable::updateNodeInfoSPFP(
        std::tuple<int,int,std::list<int>*,std::list<int>*>*  recentNodeTpl,
        std::map<int,std::tuple<int,int,std::list<int>*,std::list<int>*>*> &unVisitedNodesById){
    int p = 5; //the factor
    int src = std::get<0>(*recentNodeTpl);
    int nodeCost = std::get<1>(*recentNodeTpl);
    for(int i=0;i<linkVectorFromSrc[src]->size();i++){
        LinkInfo *info = (*linkVectorFromSrc[src])[i];
        int dest = (*linkVectorFromSrc[src])[i]->getLinkDest();
        int linkCost = (*linkVectorFromSrc[src])[i]->getLinkCost();
        int linkId = (*linkVectorFromSrc[src])[i]->getLinkId();
        bool interOrbitLink = (*linkVectorFromSrc[src])[i]->isInterOrbitLink();
        const std::vector<int> *linkVirList = (*linkVectorFromSrc[src])[i]->getVirList();
        if(info->getLinkState() && unVisitedNodesById.find((*linkVectorFromSrc[src])[i]->getLinkDest())!=unVisitedNodesById.end()){
            std::tuple<int,int,std::list<int>*,std::list<int>*>* nowTpl = unVisitedNodesById[dest];
            int updateECost;
            int virtualCostSums = 0;
            for(const auto & virtualId:*linkVirList){
                virtualCostSums += mapById[virtualId]->getLinkCost();
            }
            if(interOrbitLink)
                updateECost = (10 - p) * virtualCostSums + p * linkCost + nodeCost;
            else{
                bool isInVirtualSets = false;
                std::list<int> *recentNodeVirtualList = std::get<3>(*recentNodeTpl);
                int reverseLinkId = map[std::pair<int,int>(dest,src)]->getLinkId();
                for(const auto & virtualId:*recentNodeVirtualList){
                    if(virtualId == reverseLinkId){
                        isInVirtualSets = true;
                        break;
                    }
                }
                if(isInVirtualSets){
                    updateECost = nodeCost + 5*linkCost;
                }else{
                    updateECost = nodeCost + 10*linkCost;
                }
            }
            int nowECost = std::get<1>(*nowTpl);
            if(nowECost > updateECost){
                std::list<int> *old = std::get<2>(*recentNodeTpl),*newList = std::get<2>(*nowTpl);
                std::list<int> *oldvl = std::get<3>(*recentNodeTpl),*newvl = std::get<3>(*nowTpl);
                std::get<1>(*nowTpl) = updateECost;
                newList->clear();
                newList->assign(old->begin(),old->end());
                newList->push_front(linkId);
                newvl->clear();
                newvl->assign(oldvl->begin(), oldvl->end());
                for(auto virLinkId:*linkVirList){
                    newvl->push_front(virLinkId);
                }
            }
        }
    }
}
void LinkInfoTable::updateNodeInfo(
        std::tuple<int,int,std::list<int>*>*  recentNodeTpl,
        std::map<int,std::tuple<int,int,std::list<int>*>*> &unVisitedNodesById){
    int src = std::get<0>(*recentNodeTpl);
    int nodeCost = std::get<1>(*recentNodeTpl);
    for(int i=0;i<linkVectorFromSrc[src]->size();i++){
        LinkInfo *info = (*linkVectorFromSrc[src])[i];
        int dest = (*linkVectorFromSrc[src])[i]->getLinkDest();
        int linkCost = (*linkVectorFromSrc[src])[i]->getLinkCost();
        int linkId = (*linkVectorFromSrc[src])[i]->getLinkId();
        if(info->getLinkState() && unVisitedNodesById.find((*linkVectorFromSrc[src])[i]->getLinkDest())!=unVisitedNodesById.end()){
            std::tuple<int,int,std::list<int>*>* nowTpl = unVisitedNodesById[dest];
            int nowCost;
            nowCost = std::get<1>(*nowTpl);
            if(nowCost >= linkCost + nodeCost){
                std::list<int> *old = std::get<2>(*recentNodeTpl),*newList = std::get<2>(*nowTpl);
                std::get<1>(*nowTpl) = linkCost + nodeCost;
                newList->clear();
                newList->assign(old->begin(),old->end());
                newList->push_front(linkId);
            }
        }
    }
}
void  LinkInfoTable::reCalculateSPFP(std::map<int,std::list<int>*> *oldrt){
    for(auto rt:*oldrt){
        rt.second->clear();
    }
    int nodeNum = linkVectorFromSrc.size();
    if(oldrt->size()==0){
        for(int i=0;i<nodeNum;i++) (*oldrt)[i] = new std::list<int>();
    }
    std::list<std::tuple<int,int,std::list<int>*,std::list<int>*>*> visitedNodes,unVisitedNodes;
    std::tuple<int,int,std::list<int>*,std::list<int>*>* recentNodeTpl;
    std::map<int,std::tuple<int,int,std::list<int>*,std::list<int>*>*> unVisitedNodesById;
    std::tuple<int,int,std::list<int>*,std::list<int>*> tuple[nodeNum];
    for(int i=0;i<nodeNum;i++){
        std::get<0>(tuple[i]) = i;
        if(i == leoId){
            std::get<1>(tuple[i]) = 0;
            std::get<2>(tuple[i]) = new std::list<int>(); //Physical links
            std::get<3>(tuple[i]) = new std::list<int>(); //Virtual links
            visitedNodes.push_front(&tuple[i]);
            recentNodeTpl = &tuple[i];
        }
        else{
            std::get<1>(tuple[i]) = INT_MAX;
            std::get<2>(tuple[i]) = new std::list<int>();
            std::get<3>(tuple[i]) = new std::list<int>(); //Virtual links
            unVisitedNodes.push_front(&tuple[i]);
            unVisitedNodesById[i] = &tuple[i];
        }
    }
    while(!unVisitedNodes.empty()){
        updateNodeInfoSPFP(recentNodeTpl,unVisitedNodesById);
        std::list<std::tuple<int,int,std::list<int>*,std::list<int>*>*>::iterator iter = searchNearestSPFP(unVisitedNodes);
        unVisitedNodesById.erase(unVisitedNodesById.find(std::get<0>(**iter)));
        visitedNodes.push_front(*iter);
        recentNodeTpl = *iter;
        unVisitedNodes.erase(iter);
    }
    std::cout<<std::endl;
    for(auto iter=visitedNodes.begin();iter!=visitedNodes.end();iter++){
        std::tuple<int,int,std::list<int>*,std::list<int>*> *item ;
        item = *iter;
        (*oldrt)[std::get<0>(*item)]->merge(*std::get<2>(*item));
        std::get<2>(*item)->clear();
        std::get<3>(*item)->clear();
        delete std::get<2>(*item);
        delete std::get<3>(*item);
    }
    visitedNodes.clear();
    std::cout<<"Time: "<<simTime()<<std::endl;
    for(const auto &linkId:*(*oldrt)[61]){
        std::cout<<linkId<<" ";
    }
    std::cout<<std::endl;
}
void  LinkInfoTable::reCalculateSPF(std::map<int,std::list<int>*> *oldrt){
    for(auto rt:*oldrt){
        rt.second->clear();
    }
    int nodeNum = linkVectorFromSrc.size();
    if(oldrt->size()==0){
        std::cout<<"Initialize the rt for "<<nodeNum<<" nodes"<<std::endl;
        for(int i=0;i<nodeNum;i++) (*oldrt)[i] = new std::list<int>();
    }
    std::list<std::tuple<int,int,std::list<int>*>*> visitedNodes,unVisitedNodes;
    std::tuple<int,int,std::list<int>*>* recentNodeTpl;
    std::map<int,std::tuple<int,int,std::list<int>*>*> unVisitedNodesById;
    std::tuple<int,int,std::list<int>*> tuple[nodeNum];
    for(int i=0;i<nodeNum;i++){
        std::get<0>(tuple[i]) = i;
        if(i == leoId){
            std::get<1>(tuple[i]) = 0;
            std::get<2>(tuple[i]) = new std::list<int>();
            visitedNodes.push_front(&tuple[i]);
            recentNodeTpl = &tuple[i];
        }
        else{
            std::get<1>(tuple[i]) = INT_MAX;
            std::get<2>(tuple[i]) = new std::list<int>();
            unVisitedNodes.push_front(&tuple[i]);
            unVisitedNodesById[i] = &tuple[i];
        }
    }
    while(!unVisitedNodes.empty()){
//        std::cout<<"now node:"<< std::get<0>(*recentNodeTpl)<< std::endl;
        updateNodeInfo(recentNodeTpl,unVisitedNodesById);
        std::list<std::tuple<int,int,std::list<int>*>*>::iterator iter = searchNearest(unVisitedNodes);
        unVisitedNodesById.erase(unVisitedNodesById.find(std::get<0>(**iter)));
        visitedNodes.push_front(*iter);
        recentNodeTpl = *iter;

        unVisitedNodes.erase(iter);
    }
    std::cout<<std::endl;
    for(auto iter=visitedNodes.begin();iter!=visitedNodes.end();iter++){
        std::tuple<int,int,std::list<int>*> *item ;
        item = *iter;
        (*oldrt)[std::get<0>(*item)]->merge(*std::get<2>(*item));
        std::get<2>(*item)->clear();
        delete std::get<2>(*item);
    }
    visitedNodes.clear();

}

int LipsinRouteConfigurator::getIntAttrOrPar(const cXMLElement& ifConfig, const char *name) const
{
    const char *attrStr = ifConfig.getAttribute(name);
    if (attrStr && *attrStr)
        return atoi(attrStr);
    return par(name);
}

bool LipsinRouteConfigurator::getBoolAttrOrPar(const cXMLElement& ifConfig, const char *name) const
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
std::string LipsinRouteConfigurator::getStrAttrOrPar(const cXMLElement& ifConfig, const char *name) const
{
    const char *attrStr = ifConfig.getAttribute(name);
    return std::string(attrStr);
}
void LipsinRouteConfigurator::loadPhyInterfaceParameters(const cXMLElement& linkConfig)
{
    std::vector<int> virlist;
    int srcId = getIntAttrOrPar(linkConfig,"srcId"),
            destId = getIntAttrOrPar(linkConfig,"destId"),
            cost = getIntAttrOrPar(linkConfig,"cost"),
            linkId = getIntAttrOrPar(linkConfig,"linkId");
    std::string linkTypeString = getStrAttrOrPar(linkConfig,"linkType");

    bool interLink = (linkTypeString == std::string("inter-orbit"));
    if(interLink){
        std::string virlistString = getStrAttrOrPar(linkConfig,"virList");
        std::string tmp("");
        for(const auto & c:virlistString){
            if(c==','){
                virlist.push_back(std::stoi(tmp));
                tmp = "";
            }else tmp += c;
        }
        if(tmp!="") virlist.push_back(std::stoi(tmp));
    }

    if(srcId < 0 || destId < 0 || cost < 0)
        cRuntimeError("Unknown link Interface set at %s",
                         linkConfig.getSourceLocation());
    //add into LipsinRouteTable
    table->addLinkInfo(srcId, destId, linkId, cost, true, interLink, virlist);
}
bool LipsinRouteConfigurator::loadConfigFromXML(cXMLElement *linksConfig)
{
    if(strcmp(linksConfig->getTagName(), "LIPSINConfig"))
        throw cRuntimeError("Cannot read LIPSIN configuration, unexpected element '%s' at %s", linksConfig->getTagName(), linksConfig->getSourceLocation());
    cModule *myNode = findContainingNode(genModule);
    ASSERT(myNode);
    std::string nodeFullPath = myNode->getFullPath();
    std::string nodeShortenedFullPath = nodeFullPath.substr(nodeFullPath.find('.') + 1);
    cXMLElementList routers = linksConfig->getElementsByTagName("Router");
    for(auto & router : routers){
        cXMLElementList routerConfig = router->getChildren();
        for (auto & linkConfig : routerConfig) {
            std::string nodeName = linkConfig->getTagName();
            if ((nodeName == "PhysicalLink"))
                loadPhyInterfaceParameters(*linkConfig);
        }
    }
    return true;
}

} /* namespace lipsin*/
} /* namespace inet */
