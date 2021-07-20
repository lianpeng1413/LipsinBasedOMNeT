/*
 * routingTable.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/router/route/routingTable.h"

#include <list>
#include <string>
#include <algorithm>
#include <sstream>

#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/PatternMatcher.h"
#include "inet/common/Simsignals.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/routing/nlsr/Nlsr.h"
#include "inet/routing/nlsr/router/route/map.h"
#include "inet/routing/nlsr/router/route/routingTableCalculator.h"
#include "inet/routing/nlsr/router/route/routingTableEntry.h"
#include "inet/routing/nlsr/router/route/namePrefixTable.h"

namespace inet{
namespace nlsr {

using namespace utils;

Define_Module(RoutingTable);
//Register_Abstract_Class(inet::nlsr::RoutingTable::routingChanged);
//
//const simsignal_t RoutingTable::routingChangedSignal = cComponent::registerSignal("routingChangedSignal");

void RoutingTable::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_LOCAL)
    {
        cModule *host = getContainingNode(this);
        forwarding = par("forwarding");
        const char* nodeName = getContainingNode(this)->getName();
        std::string str(nodeName);
        std::string node;
        node.append(str);
        routerId.set("LEOSat", "orbit", node);
    }
}

void RoutingTable::handleMessage(cMessage *msg){}

cModule *RoutingTable::getHostModule()
{
    return findContainingNode(this);
}

RoutingTable::~RoutingTable()
{
    //Test name register function right or not: output register name infor
//    std::ofstream routingTable;
//    auto routeFile = std::string("routingTable.txt");
//    routingTable.open(routeFile, std::ofstream::app);
//
//    routingTable << "Router name: " << routerId.str() << ", routing info: "<< ", at time: " << simTime() << endl;
//    auto its = m_rTable.begin();
//    for ( ; its!= m_rTable.end(); its++){
//        routingTable << (*its).getDestination().str() << ", nexthopList: " << (*its).getNexthopList().size() << endl;
//    }
//    routingTable.close();

    clearRoutingTable();
    clearDryRoutingTable();
}

void RoutingTable::calculate()
{
    EV_INFO << " Clear old routing table.\n";
    clearRoutingTable();
    clearDryRoutingTable();    //for dry run options;

    EV_INFO << " calculate routing table.\n";
    calculateLsRoutingTable(); //calculate Link State routing

//    std::ofstream routingTable;
//    path = m_lsdb->getRouter()->getRCTpath();
//    auto fileName = std::string("syncInterval_") + std::to_string(m_lsdb->getRouter()->getSyncInterval());
//    routingTable.open(path + fileName + std::string(".txt"), std::ofstream::app);
//
//    routingTable << "Router name: " << routerId.str() << ", routing changed at time: " << simTime() << endl;
//    auto its = m_rTable.begin();
//    for ( ; its!= m_rTable.end(); its++){
//        routingTable << "destination router: " << (*its).getDestination().str() << ", nexthopList size: " << (*its).getNexthopList().size() << endl;
//        routingTable << (*its).getNexthopList().getNextHop().str() << ", next interface: "<< (*its).getNexthopList().getNextHop().getIfIndex() << endl;
//    }
//    routingTable.close();
}

void RoutingTable::calculateLsRoutingTable()
{
    EV_INFO << "router calculateLsRoutingTable: " << routerId.str() << ", at: " << simTime() << endl;
    Map map;
    auto adjLsa = m_lsdb->getAdjLsdb();
    map.createFromAdjLsdb(adjLsa.begin(), adjLsa.end());
    size_t nRouters = map.getMapSize();
    LinkStateRoutingTableCalculator calculator(nRouters, m_lsdb->getRouter());
    calculator.calculatePath(map, *this, adjLsa);
}

static bool routingTableEntryCompare(RoutingTableEntry& rte, iName& destRouter)
{
  return rte.getDestination() == destRouter;
}

//checked by Lianpeng.
void RoutingTable::addNextHop(const iName& destRouter, NextHop& nh)
{
    RoutingTableEntry* rteChk = findRoutingTableEntry(destRouter);
    if (rteChk == nullptr) {
        RoutingTableEntry rte(destRouter);
        rte.getNexthopListForUpdate().addNextHop(nh);
        m_rTable.push_back(rte);

        EV_INFO << "Tell NPT With new Route.\n";
    }
    else {
        rteChk->getNexthopListForUpdate().addNextHop(nh);
    }
    // Inform the NPT that updates have been made.  checked by yanfei11.11
//    routingChanged routingTableChanged(m_rTable);
//    emit(routingChangedSignal, &routingTableChanged);
    m_lsdb->getRouter()->getNamePrefixTable()->updateWithNewRoute(m_rTable);
}

RoutingTableEntry* RoutingTable::findRoutingTableEntry(const iName& destRouter)
{
    auto it = std::find_if(m_rTable.begin(), m_rTable.end(),
                         std::bind(&routingTableEntryCompare, std::placeholders::_1, destRouter));
    if (it != m_rTable.end()) {
        return &(*it);
    }
    return nullptr;
}

void RoutingTable::addNextHopToDryTable(const iName& destRouter, NextHop& nh)
{
    EV_INFO << "Adding " << nh << " to dry table for destination: " << destRouter << endl;

    auto it = std::find_if(m_dryTable.begin(), m_dryTable.end(),
            std::bind(&routingTableEntryCompare, std::placeholders::_1, destRouter));
    if (it == m_dryTable.end()) {
        RoutingTableEntry rte(destRouter);
        rte.getNexthopListForUpdate().addNextHop(nh);
        m_dryTable.push_back(rte);
    }
    else {
        it->getNexthopListForUpdate().addNextHop(nh);
    }
}

void RoutingTable::clearRoutingTable()
{
    if (m_rTable.size() > 0) {
        m_rTable.clear();
    }
}

void RoutingTable::clearDryRoutingTable()
{
    if (m_dryTable.size() > 0) {
        m_dryTable.clear();
    }
}

std::list<RoutingTableEntry>& RoutingTable::getRoutingTable()
{
    return m_rTable;
}

bool RoutingTable::handleOperationStage(LifecycleOperation * operation, IDoneCallback *doneCallback)
{
    Enter_Method_Silent();
    int stage = operation->getCurrentStage();
    if (dynamic_cast<ModuleStartOperation *>(operation))
    {
    }
    else if (dynamic_cast<ModuleStopOperation *>(operation))
    {
        if (static_cast<ModuleStopOperation::Stage>(stage) == ModuleStopOperation::STAGE_NETWORK_LAYER)
        {
        }
    }
    else if (dynamic_cast<ModuleCrashOperation *>(operation))
    {
        if (static_cast<ModuleCrashOperation::Stage>(stage) == ModuleCrashOperation::STAGE_CRASH)
        {
        }
    }
    return true;
}

} // namespace nlsr
} // namespace inet



