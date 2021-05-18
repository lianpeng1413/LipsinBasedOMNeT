/*
 * LipsinRouteConfigurator.h
 *
 *  Created on: Apr 12, 2021
 *      Author: root
 */

#ifndef INET_APPLICATIONS_GENERIC_LIPSINROUTE_LIPSINROUTECONFIGURATOR_H_
#define INET_APPLICATIONS_GENERIC_LIPSINROUTE_LIPSINROUTECONFIGURATOR_H_

#include <vector>
#include <map>
#include "inet/common/INETDefs.h"

namespace inet {
namespace lipsin{
class LinkInfo{
private:
    int src;
    int dest;
    int id;
    int cost;
    bool state;
    bool interOrbitType;
    std::vector<int> *virList;
public:
    void setLinkDown(){ state = false;}
    void setLinkUp(){ state = true;}
    void setLinkCost(int c){ cost = c ;}
    int getLinkDest(){ return dest;}
    bool getLinkState(){ return state;}
    bool isInterOrbitLink(){ return interOrbitType; }
    int getLinkId(){ return id;}
    int getLinkCost(){ return cost;}
    const std::vector<int> * getVirList() const { return virList;}
    LinkInfo(int s,int d,int id,int c,bool state,bool linkType,std::vector<int> &virVector):src(s),dest(d),id(id),cost(c),state(state),interOrbitType(linkType){
        virList = new std::vector<int>;
        for( const auto & virInfo:virVector){
            virList->push_back(virInfo);
        }
    }
    ~LinkInfo(){ virList->clear();delete virList;}
};
class LinkInfoTable{
private:
    std::map<std::pair<int,int>,LinkInfo*> map;
    std::map<int,LinkInfo*> mapById;
    std::map<int,std::vector<LinkInfo*>*> linkVectorFromSrc;
    int leoId;
    cModule *genModule;
protected:
    void updateNodeInfo(
            std::tuple<int,int,std::list<int>*>*  recentNodeTpl,
            std::map<int,std::tuple<int,int,std::list<int>*>*> &unVisitedNodesById);
    void updateNodeInfoSPFP(
            std::tuple<int,int,std::list<int>*,std::list<int>*>*  recentNodeTpl,
            std::map<int,std::tuple<int,int,std::list<int>*,std::list<int>*>*> &unVisitedNodesById);
    std::list<std::tuple<int,int,std::list<int>*>*>::iterator searchNearest(std::list<std::tuple<int,int,std::list<int>*>*> &unVisitedNodes);
    std::list<std::tuple<int,int,std::list<int>*,std::list<int>*>*>::iterator searchNearestSPFP(std::list<std::tuple<int,int,std::list<int>*,std::list<int>*>*> &unVisitedNodes);
public:
    LinkInfoTable(cModule *module);
    virtual ~LinkInfoTable();
    void addLinkInfo(int src,int dest,int linkId,int cost,bool state,bool interOrbitType,std::vector<int> &virlist);
    void changeLinkDown(int src, int dest);
    void changeLinkUp(int src, int dest);
    void changeLinkCost(int src,int dest,int cost);
    void  reCalculateSPF(std::map<int,std::list<int>*> *oldrt);
    void reCalculateSPFP(std::map<int,std::list<int>*> *oldrt);
};
class INET_API LipsinRouteConfigurator {
public:
    LipsinRouteConfigurator(cModule *module,LinkInfoTable *t):genModule(module),table(t){}
    ~LipsinRouteConfigurator(){}
    bool loadConfigFromXML(cXMLElement *linksConfig);
private:
    cModule *genModule = nullptr;
    LinkInfoTable *table;
    cPar& par(const char *name) const { return genModule->par(name); }
    int getIntAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    bool getBoolAttrOrPar(const cXMLElement& ifConfig, const char *name) const;
    std::string getStrAttrOrPar(const cXMLElement& ifConfig, const char *name) const;

    /**
     * Loads OSPF configuration information for a router interface.
     * Handles POINTTOPOINT, BROADCAST, NBMA and POINTTOMULTIPOINT interfaces.
     */
    void loadPhyInterfaceParameters(const cXMLElement& linkConfig);

};

}/* namespace lipsin*/
}/* namespace inet */

#endif /* INET_APPLICATIONS_GENERIC_LIPSINROUTE_LIPSINROUTECONFIGURATOR_H_ */
