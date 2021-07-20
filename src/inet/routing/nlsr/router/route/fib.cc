/*
 * fib.cc
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */

#include "fib.h"

#include <map>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <memory>

#include "inet/common/ModuleAccess.h"
#include "inet/common/Simsignals.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/nlsr/router/route/fibEntry_m.h"
#include "inet/routing/nlsr/router/route/nextHopList.h"
#include "inet/routing/nlsr//neighbor/adjacencyList.h"

namespace inet{
namespace nlsr{

Define_Module(Fib);

//const std::string Fib::MULTICAST_STRATEGY("/localhost/nfd/strategy/multicast");
//const std::string Fib::BEST_ROUTE_V2_STRATEGY("/localhost/nfd/strategy/bestRoute");

void Fib::finish(){}

Fib::~Fib(){}

void Fib::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        cModule *host = getContainingNode(this);
        forwarding = par("forwarding");

        auto name = getParentModule()->getFullPath();
        name = name + ".adjList";
        auto path = name.c_str();
        auto mod = this->getModuleByPath(path);
        m_adjacencyList = dynamic_cast<AdjacencyList *>(mod);
    }
}

void Fib::handleMessage(cMessage *msg){}


cModule *Fib::getHostModule()
{
    return findContainingNode(this);
}

shared_ptr<FibEntry> Fib::lookup(const iName& name)
{
    auto iter = fib.find(name);

    if(iter != fib.end()) {
        return iter->second; // return fib entry.
    }
    else{
        return nullptr;
    }
}

void Fib::remove(const iName &name)
{
    EV_INFO << "Fib::remove called.\n";
    fib.erase(name);
}

void Fib::updateNextHop(int intf)
{
    for(auto it = fib.begin(); it != fib.end(); it++) {
        auto iter = it->second->getM_nexthopListForUpdate().begin();
        if(iter != it->second->getM_nexthopListForUpdate().end()){
            if(iter->getIfIndex() == intf){
                EV_INFO << "removing nextHop from fib. " << "\n";
                auto nextHops = it->second->getM_nexthopListForUpdate().getNextHops(intf); //get nextHops by ie.

                for(auto iterr = nextHops->begin();iterr != nextHops->end(); ++iterr)
                {
                    auto nh = *iterr;
                    it->second->getM_nexthopListForUpdate().removeNextHop(nh);
                }
                nextHops->clear();
            }
            iter++;
        }
    }
}

//TODO modify update checked by yanfei 20201111
void Fib::update(const iName& name, const NexthopList& allHops)
{
    EV_INFO << "Fib::update called. \n";
    // Get the max possible faces
    unsigned int maxFaces = getNumberOfFacesForName(allHops);

    NexthopList hopsToAdd;
    unsigned int nFaces = 0;

    // Create a list of next hops to be installed with length == maxFaces
    for (auto it = allHops.cbegin(); it != allHops.cend() && nFaces < maxFaces; ++it, ++nFaces) {
        hopsToAdd.addNextHop(*it);
    }

    auto entryIt = fib.find(name);

    // New FIB entry that has nextHops
    if (entryIt == fib.end() && hopsToAdd.size() != 0) {
        EV_INFO << "New FIB Entry. \n";

//        std::shared_ptr<FibEntry> entry; //issue: empty entry!
        std::shared_ptr<FibEntry> entry = std::make_shared<FibEntry> (name);
        addNextHopsToFibEntry(name, entry, hopsToAdd);

        fib.emplace(name, entry);

        entryIt = fib.find(name);
    }
    // Existing FIB entry that may or may not have nextHops
    else {
        // Existing FIB entry
        EV_INFO << "Existing FIB Entry" << endl;

        // Remove empty FIB entry
        if (hopsToAdd.size() == 0) {
            remove(name);
            return;
        }

        std::shared_ptr<FibEntry> entry = (entryIt->second);
        addNextHopsToFibEntry(name, entry, hopsToAdd);

        std::set<NextHop, NextHopComparator> hopsToRemove;
        std::set_difference(entry->getM_nexthopListForUpdate().begin(), entry->getM_nexthopListForUpdate().end(), hopsToAdd.begin(), hopsToAdd.end(),
                        std::inserter(hopsToRemove, hopsToRemove.end()), NextHopComparator());

        bool isUpdatable = isNotNeighbor(name);
        // Remove the uninstalled next hops from NFD and FIB entry
        for (const auto& hop : hopsToRemove){
            EV_INFO << "Removing " << hop.getIfIndex() << " from " << entry->getM_nexthopList().getNextHop().getNextHop().str() << endl;
            entry->getM_nexthopListForUpdate().removeNextHop(hop);
        }

        // Increment sequence number
        entry->setM_seqNo(entry->getM_seqNo() + 1);

        entryIt = fib.find(name);

    }
}

void Fib::addNextHopsToFibEntry(const iName& name, std::shared_ptr<FibEntry> entry, const NexthopList& hopsToAdd)
{
  bool shouldRegister = isNotNeighbor(name);

  for (const auto& hop : hopsToAdd.getNextHops())
  {
    // Add nexthop to FIB entry
    entry->getM_nexthopListForUpdate().addNextHop(hop);
  }
}

unsigned int Fib::getNumberOfFacesForName(const NexthopList& nextHopList)
{
    uint32_t nNextHops = static_cast<uint32_t>(nextHopList.getNextHops().size());

    // Allow all faces
    return nNextHops;
}

bool Fib::isNotNeighbor(const iName& name)
{
  return !m_adjacencyList->isNeighbor(name);
}

} // namespace nlsr
} // namespace inet


