/*
 * pitBase.cc
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#include "pitBase.h"
#include <fstream>

namespace inet
{

Define_Module(pitBase);

void pitBase::finish()
{
    for (auto &iter : *timers)
    {
        cancelAndDelete(iter.first);
        interests->erase(iter.second);
    }
    delete timers;
    delete table;
    delete interests;
}

pitBase::~pitBase()
{

}

void pitBase::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        table = new std::multimap<iName, pitEntry>;
        timers = new timerTable;
        interests = new std::map<iName, cMessage *>;

        auto name = getParentModule()->getFullPath();
        name = name + ".fib";
        auto path = name.c_str();
        auto mod = this->getModuleByPath(path);
        rt = dynamic_cast<fibBase *>(mod);
    }
}

void pitBase::handleMessage(cMessage *msg)
{
    // delete PIT item regularly
    auto interest = timers->find(msg)->second;

    removeEntry(interest);
//    cancelEvent(msg);
}

void pitBase::printPIT(std::ostream &out)
{
    for (auto iter = table->begin(); iter != table->end();)
    {
        auto range = table->equal_range(iter->first);
        out << "NIDs name is: ";
        for (auto it = range.first; it != range.second; it++)
            out << it->second.getNidName().str() << "  ";
        out << endl;
        out << "TTL is: " << iter->second.getTTL() << " , nextMac: " << iter->second.getMac() << endl;
        iter = range.second;
    }
}

bool pitBase::haveEntry(const iName& interest, long nonce)
{
    auto iter = table->find(interest);
    if(iter != table->end() && iter->second.getNonce() == nonce)
        return true;
    else
        return false;
}

void pitBase::record(const pitBase::Entry &entry)
{
    std::ofstream outfile;
    auto fileName = this->getParentModule()->getParentModule()->getName() + std::string("_pitTest.txt");
    outfile.open("./simu/" + fileName, std::ofstream::app);
    simtime_t time = simTime();
    outfile << "pit created at: " << time << " ," << entry.first.str() << "," << entry.second.getNidName() << endl;
    outfile.close();
}

const pitBase::Entry &pitBase::createEntry(const iName &interest, const iName &nid,
                                          const MacAddress &mac, simtime_t t, int interfaceId, long Nonce, bool served, bool is_consumer)
{
    Enter_Method("createEntry()");

    //if timer has setting, fresh it.
    auto timer = interests->find(interest);
    if (timer != interests->end())
    {
        cancelEvent(timer->second);
        scheduleAt(simTime() + t, timer->second);
    }
    //else create a new timer for interest.
    else
    {
        cMessage *newTimer = new cMessage("timer");
        (*timers)[newTimer] = interest;
        (*interests)[interest] = newTimer;
        scheduleAt(simTime() + t, newTimer);
    }

    // check pit, NONCE can be used to determine the interest is a re-send interest,
    auto range = table->equal_range(interest);
    for (auto iter = range.first; iter != range.second; iter++)
    {
        //check interest has served or not.
        if (Nonce == iter->second.getNonce())
            return *iter;
    }

    pitEntry nt(nid, t, mac, interfaceId, Nonce, served, is_consumer);
    auto entry = std::make_pair(interest, nt);
    addPitEntry(entry);

//    record(entry);
    return entry;
}

void pitBase::addPitEntry(const pitBase::Entry &entry)
{
    table->insert(entry);
}

void pitBase::removeEntry(const iName &interest)
{
    auto pointer = interests->find(interest)->second;
    timers->erase(pointer);
    cancelAndDelete(pointer);

    table->erase(interest);
    interests->erase(interest);
}

void pitBase::removeEntry(const std::multimap<iName, pitEntry>::iterator iter)
{
    table->erase(iter);
}

pitBase::EntrysRange pitBase::findPitEntry(const iName &interest)
{
    return table->equal_range(interest);
}

bool pitBase::isConsumer(const iName &interest)
{
    auto range = table->equal_range(interest);
    for (auto iter = range.first; iter != range.second; iter++)
    {
        if (iter->second.isConsumer())
            return true;
    }
    return false;
}

bool pitBase::servedForThisInterest(const iName& interest, unsigned long Nonce)
{
    auto range = table->equal_range(interest);
    for (auto iter = range.first; iter != range.second; iter++)
    {
        if(iter->second.getNonce() == Nonce && iter->second.getServed())
            return true;
    }
    return false;
}

void pitBase::setServed(const iName &interest)
{
    auto range = table->equal_range(interest);
    for (auto iter = range.first; iter != range.second; iter++)
    {
            iter->second.setServed(true);
    }
}
} // namespace inet




