/*
 * NlsrRouter.cc
 *
 *  Created on: Aug 23, 2020
 *      Author: root
 */
#include <algorithm>

#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/routing/nlsr/router/NlsrArea.h"
#include "inet/routing/nlsr/router/route/routingTable.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/router/route/namePrefixTable.h"

namespace inet{
namespace nlsr{

Router::Router(cSimpleModule *containingModule, IInterfaceTable*ift, RoutingTable *rts, Fib *fib, int syncInterval, std::string RCTpath, double sendInterval)
    : ifts(ift)
    , rt(rts)
    , m_fib(fib)
    , syncInterval(syncInterval)
    , RCTpath(RCTpath)
    , sendInterval(sendInterval)
{
    m_adjl = new AdjacencyList;
    m_npl = new NamePrefixList;
    m_namePrefixTable = new NamePrefixTable(m_fib, rt);

    m_fib->setAdjList(m_adjl);

    messageHandler = new MessageHandler(this, containingModule);
    ageTimer = new cMessage("Router::DatabaseAgeTimer", DATABASE_AGE_TIMER);
    ageTimer->setContextPointer(this);
    messageHandler->startTimer(ageTimer, 1.0);

    const char* nodeName = containingModule->getParentModule()->getParentModule()->getName();
    std::string str(nodeName);
    std::string node;
    node.append(str);
    routerName.set("LEOSat", "orbit", node);
}

Router::~Router()
{
    long areaCount = areas.size();
    for (long i=0; i < areaCount; ++i) {
        delete areas[i];
    }

    messageHandler->clearTimer(ageTimer);
    delete ageTimer;
    delete messageHandler;
    delete m_adjl;
    delete m_npl;
    delete m_namePrefixTable;
}

void Router::addWatches()
{
    WATCH(routerName);
//    WATCH_PTRVECTOR(nameLsa);
//    WATCH_PTRVECTOR(adjLsa);
//    WATCH_PTRVECTOR(rt);
}

void Router::addArea(NlsrArea *area)
{
    area->setRouter(this);
    rt->setArea(area);
    areasByID[area->getAreaID()] = area;
    areas.push_back(area);
}

std::vector<AreaId> Router::getAreaIds()
{
    std::vector<AreaId> areaIds;
    for(auto &entry : areas)
        areaIds.push_back(entry->getAreaID());
    return areaIds;
}

NlsrArea *Router::getAreaByID(AreaId areaID)
{
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end()) {
        return areaIt->second;
    }
    else {
        return nullptr;
    }
}

void Router::addNeighbors(Neighbor *neighbor)
{
    m_Neighbors.push_back(neighbor);
}

uint32_t Router::getMaxFacesPerPrefix(const iName& name)
{
//    m_maxFacesPerPrefix = nameFromInterface.count(name);
    m_maxFacesPerPrefix = 3;
    return m_maxFacesPerPrefix;
}

void Router::nameRegisterFunction(const iName& interest, iName & originRouter)
{
    EV_INFO << "Registered interest name." << interest.str() << endl;

    m_npl->insert(interest, originRouter.str());  //put into namePrefixList

    /* Generate nameLSA and install it into adjLSDB.
     * nameLSA name: /Neighbor/NAMELSA/localRouter.*/
    iName lsaName;
    unsigned long seqNo = 0;
    lsaName.set(originRouter.str().erase(0, 1), "NAMELSA", "0"); //Generate in local
    NlsrNameLsa *nameLsa = findNameLsa(lsaName);
    if(nameLsa != nullptr) { // do nothing or exist nameLsa: seqNo + 1
        long sequenceNumber = nameLsa->getHeader().getSeqNo();
        for(const auto& name : m_npl->getNames()){
            nameLsa->getM_nplForUpdate()->insert(name);
        }
        if (sequenceNumber == MAX_SEQUENCE_NUMBER) {
            nameLsa->getHeaderForUpdate().setSeqNo(MAX_AGE); // update it
//            nameLsa->incrementInstallTime();
            installNameLsa(nameLsa, 0);
        }
        else{
            nameLsa->getHeaderForUpdate().setSeqNo(sequenceNumber + 1);//update seqNo??
//            nameLsa->incrementInstallTime();
            installNameLsa(nameLsa, 0);
        }
    }
    else{
        EV_INFO << "Generate nameLsa: " << lsaName.str() << " ."<< endl;
        NlsrNameLsa *newNameLSA = new NlsrNameLsa;
        NlsrLsaHeader& lsaHeader = newNameLSA->getHeaderForUpdate();

        lsaHeader.setLsAge(0);
        lsaHeader.setInterestName(lsaName);
        lsaHeader.setLsType(NAME_LSA);
        lsaHeader.setHopCount(0);
        lsaHeader.setSeqNo(INITIAL_SEQUENCE_NUMBER);
        lsaHeader.setHopLimit(1);
        lsaHeader.setOriginRouter(originRouter); //set originalRouter
        lsaHeader.setLsaLength(B(NLSR_LSA_HEADER_LENGTH).get());
        newNameLSA->setM_npl(m_npl);
        newNameLSA->getHeaderForUpdate().setSeqNo(0);

        installNameLsa(newNameLSA, 0);
        delete newNameLSA;
    }
}

bool Router::installNameLsa(const NlsrNameLsa* nlsa, AreaId areaID)
{
    EV_INFO << "Install NameLsa:" << nlsa->getHeader().getInterestName().str() << "to LSDB." << endl;
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end()) {
        return areaIt->second->installNameLsaToLsdb(nlsa);
    }
    return false;
}

bool Router::installAdjLsa(const NlsrAdjLsa* alsa)
{
    EV_INFO << "Install adjLsa: " << alsa->getHeader().getInterestName().str() << " to LSDB." << endl;
    int areaID = 0;
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end()) {
        return areaIt->second->installAdjLsaToLsdb(alsa);
    }
    else
        return false;
}

NlsrNameLsa* Router::findNameLsa(const iName rName)
{// find "rName" in lsdb whether or not.
    int areaID = 0;
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end())
        return areaIt->second->findNameLsa(rName);
    else{
        return nullptr;
    }
}

NlsrAdjLsa* Router::findAdjLsa(const iName& key)
{// find "key" in lsa whether or not.
    int areaID = 0;
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end())
        return areaIt->second->findAdjLsa(key);
    else{
        return nullptr;
    }
}

std::vector<NlsrNameLsa *>& Router::getNameLsdb()
{
    int areaID = 0;
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end())
        return areaIt->second->getNameLsdb();
}

std::vector<NlsrAdjLsa *>& Router::getAdjLsdb()
{
    int areaID = 0;
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end())
        return areaIt->second->getAdjLsdb();
}

bool Router::isNameLsaNew(const iName& key, uint64_t seqNo)
{
    int areaID = 0;
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end())
        return areaIt->second->isNameLsaNew(key, seqNo);
    else{
        return true;
    }
}

bool Router::isAdjLsaNew(const iName& key, uint64_t seqNo)
{
    int areaID = 0;
    auto areaIt = areasByID.find(areaID);
    if (areaIt != areasByID.end())
        return areaIt->second->isAdjLsaNew(key, seqNo);
    else{
        return true;
    }
}

void Router::rebuildRoutingTable()
{
    EV_INFO << "--> Rebuilding routing table:\n";
//    rt->setRouter(this);
//    //Test nameLSA and adjLSA info right or not: output router lsdb info
//    std::ofstream nameLsaInfo;
//    auto nameLsaFile = std::string("nameLsaInfo.txt");
//    nameLsaInfo.open(nameLsaFile, std::ofstream::app);
//    auto its = getNameLsdb().begin();
//    for ( ; its!= getNameLsdb().end(); its++){
//        nameLsaInfo << routerName.str() << ", at " << simTime() << endl;
//        auto npl = (*its)->getM_npl()->getNames();
//        auto nplPTR = npl.begin();
//        for ( ; nplPTR!= npl.end(); nplPTR++){
//            nameLsaInfo << "names in npl: " << (*nplPTR).str() << endl;
//        }
//    }
//    nameLsaInfo.close();
//
//    std::ofstream adjLsaInfo;
//    auto adjLsaFile = std::string("adjLsaInfo.txt");
//    adjLsaInfo.open(adjLsaFile, std::ofstream::app);
//    adjLsaInfo << this->getRouterID().str() << ", at time = " << simTime() << endl;
//    auto adjLsa = getAdjLsdb();
//    auto it = adjLsa.begin();
//    for ( ; it!= adjLsa.end(); it++){
//        adjLsaInfo << (*it)->getHeader().getInterestName()<< ",seqNo: " << (*it)->getHeader().getSeqNo() << endl;
//        auto adjL = (*it)->getM_adl()->getAdjList();
//        auto adjPTR = adjL.begin();
//        for ( ; adjPTR!= adjL.end(); adjPTR++){
//            adjLsaInfo << "names in adjl: " << (*adjPTR)->getNeighborName().str() << ", cost = " << (*adjPTR)->getLinkCost() << endl;
//        }
//    }
//    adjLsaInfo.close();
//    std::cout <<" router name: " << routerName.str() << ", at time = " << simTime() << endl;
//    auto it = getAdjLsdb().begin();
//    for ( ; it!= getAdjLsdb().end(); it++){
//        auto adjL = (*it)->getM_adl()->getAdjList();
//        auto adjPTR = adjL.begin();
//        for ( ; adjPTR!= adjL.end(); adjPTR++){
//            std::cout << "names in npl: " << (*adjPTR)->getNeighborName().str() << ", cost = " << (*adjPTR)->getLinkCost() << endl;
//        }
//    }
    rt->calculate();
}

void Router::ageDatabase()
{
    bool shouldRebuildRoutingTable = false;
    for (uint32_t j = 0; j < areas.size(); j++)
        areas[j]->ageDatabase();

    if (shouldRebuildRoutingTable){
        rebuildRoutingTable();
    }
}

} // namespace nlsr
} // namespace inet


