/*
 * fibBase.cc
 *
 *  Created on: Oct 10, 2020
 *      Author: root
 */

#include <memory>

#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/Simsignals.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

#include "fibBase.h"

namespace inet
{

Define_Module(fibBase);

fibBase::~fibBase()
{
}

void fibBase::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_LOCAL)
    {
        cModule *host = getContainingNode(this);
        forwarding = par("forwarding");
    }
}

void fibBase::handleMessage(cMessage *msg)
{
}

void fibBase::CreateEntry(const iName &dest, const iName &nextHop, const MacAddress &mac, const simtime_t &ttl, int interFace, double linkQ)
{
    auto range = fib.equal_range(dest);

    for (auto iter = range.first; iter != range.second; iter++)
    {
       if((iter->second->getNextHop() == nextHop && iter->second->getNextMac() == mac))
       {
           if (ttl + simTime() > iter->second->getLifeTime())
           {
               iter->second->setLifeTime(ttl + simTime());
           }

           return;
       }

       if (iter->second->getLinkQlt() >= linkQ)
       {
           return;
       }
    }

    auto route = std::make_shared<iFib>(nextHop, mac, ttl, interFace, linkQ);
    fib.insert({dest, route});
}

void fibBase::printRoutingTable(std::ostream &out)
{
}

cModule *fibBase::getHostModule()
{
    return findContainingNode(this);
}

shared_ptr<iFib> fibBase::findRoute(iName dest)
{
    auto range = fib.equal_range(dest);
    auto result = fib.end();
    for (auto iter = range.first; iter != range.second; iter++)
    {
        if (iter->second->getLifeTime() > simTime())
        {
            if (result == fib.end() || result->second->getLinkQlt() < iter->second->getLinkQlt())
                result = iter;
        }
        else
        {
            fib.erase(iter);
            break;
        }
    }
    if (result == fib.end())
        return nullptr;
    else
        return result->second;
}



void fibBase::removeEntry(iName nid)
{
    fib.erase(nid);
}

} // namespace inet



