/*
 * LipsinTopoManager.h
 *
 *  Created on: Apr 13, 2021
 *      Author: root
 */

#ifndef INET_APPLICATIONS_GENERIC_LIPSINROUTE_LIPSINTOPOMANAGER_H_
#define INET_APPLICATIONS_GENERIC_LIPSINROUTE_LIPSINTOPOMANAGER_H_

#include "inet/applications/generic/LipsinRoute/LipsinRouteConfigurator.h"
#include "inet/common/INETDefs.h"
namespace inet {
namespace lipsin{
class TopoChangeInfo{
private:
    simtime_t time;
    int src,dest,cost=2;
    bool status;
public:
    TopoChangeInfo(simtime_t t,int src,int dest,bool status):time(t),src(src),dest(dest),status(status){}
    simtime_t getTime(){ return time;}
    int getSrc(){ return src;}
    int getDest(){ return dest;}
    int getCost(){ return cost;}
    bool getStatus(){ return status;}
};
class LipsinTopoManager {
private:
    LinkInfoTable *table;
    cSimpleModule *module;
    std::map<int,std::list<int>*> *linkSetById;
    cMessage *updateTimer = nullptr;
    std::vector<TopoChangeInfo> changeVector;
    int index=0;
    void loadDisConnectParameters(const cXMLElement& timeConfig,simtime_t &t);
    void loadConnectParameters(const cXMLElement& timeConfig,simtime_t &t);
    const char *getStrAttr(const cXMLElement& ifConfig, const char *name) const;
public:

    cMessage *getUpdateTimer(){ return updateTimer;}
    LipsinTopoManager(LinkInfoTable *t,cSimpleModule *module,std::map<int,std::list<int>*> *linkSet):table(t),module(module),linkSetById(linkSet){ updateTimer = new cMessage("updateTimer");}
    bool loadConfigFromXML(cXMLElement *topoChangeConfig);
    bool changeTopo();
    bool scheduleTopoChange();
    ~LipsinTopoManager(){}

};

} /*namespace lipsin*/
}/* namespace inet */

#endif /* INET_APPLICATIONS_GENERIC_LIPSINROUTE_LIPSINTOPOMANAGER_H_ */
