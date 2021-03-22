/*
 * cacheTable.cc
 *
 *  Created on: Oct 1, 2020
 *      Author: root
 */
#include <algorithm>

#include "cacheTable.h"
#include "inet/common/INETDefs.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/Simsignals.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"

namespace inet{

Define_Module(cacheTable);

void cacheTable::finish()
{
    for(auto iter = timers->begin(); iter != timers->end(); iter++)
    {
        delete iter->first;
    }
    timers->clear();

    // clear all contents
    for_each(table.begin(), table.end(), [](std::pair<iName, shared_ptr<contentBlock>> entry) {
        entry.second->flush();
    });
    delete timers;
}

void cacheTable::clear()
{
    for(auto iter = timers->begin(); iter != timers->end(); iter++)
    {
        delete iter->first;
    }
    timers->clear();

    // clear all contents
    for_each(table.begin(), table.end(), [](std::pair<iName, shared_ptr<contentBlock>> entry) {
        entry.second->flush();
    });
}

void cacheTable::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        owner = getContainingNode(this);
        mtu = par("mtu").intValue();

        timers = new timerTable;
    }
    else if (stage == INITSTAGE_NETWORK_LAYER)
    {
        cModule *node = findContainingNode(this);
        NodeStatus *nodeStatus = node ? check_and_cast_nullable<NodeStatus *>(node->getSubmodule("status")) : nullptr;
        isNodeUp = !nodeStatus || nodeStatus->getState() == NodeStatus::UP;
    }
}

void cacheTable::handleMessage(cMessage *timer)
{
    //find interest
    auto interest = timers->find(timer)->second;
    auto block = table.find(interest)->second;

    remain += block->getBlockSize();

    table.erase(interest);
    timers->erase(timer);
    cancelAndDelete(timer);
}

void cacheTable::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
    if (getSimulation()->getContextType() == CTX_INITIALIZE)
        return; // ignore notifications during initialize

    Enter_Method_Silent();
    printSignalBanner(signalID, obj, details);
}

bool cacheTable::handleOperationStage(LifecycleOperation * operation, IDoneCallback *doneCallback)
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

void cacheTable::printCacheTable(std::ostream &out)
{
    for (auto iter = table.begin(); iter != table.end(); iter++)
    {
        out << iter->second->str() << endl;
    }
}

shared_ptr<contentBlock> cacheTable::getBlock(const iName& interest)
{
    auto result = table.find(interest);
    if (result != table.end())
        return result->second;
    else
        return nullptr;
}

shared_ptr<contentBlock> cacheTable::createBlock(const iName& interest)
{
    //create item with interest
    shared_ptr<contentBlock> block = std::make_shared<contentBlock>(interest, mtu);
    table[interest] = block;

    //create timer for interest
    cMessage *timer = new cMessage("timer");
    (*timers)[timer] = interest;
    return block;
}

void cacheTable::cachePacket(const iName& interest, Packet *packet)
{
    auto iter = table.find(interest);
    if (iter != table.end())
    {
        // if there's interest item, insert it.
        iter->second->insterPacket(packet);
    }
    else
    {
        //create block and insert interest into block.
        createBlock(interest);
        iter = table.find(interest);

        if (iter == table.end())
            std::cout << "end!" << endl;
        auto ptr = iter->second;
        iter->second->insterPacket(packet);
    }
}

bool cacheTable::hasThisPacket(Packet *packet, const iName& interest)
{
    auto iter = table.find(interest);
    if (iter == table.end())
    {
        return false;
    }
    else
    {
        return iter->second->hasThisPacket(packet);
    }
}
}
