/*
 * pitBase.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_NDN_PIT_PITBASE_H_
#define INET_NETWORKLAYER_NDN_PIT_PITBASE_H_

#include <map>
#include <iostream>

#include "inet/common/INETDefs.h"
#include "inet/networklayer/ndn/FIB/fibBase.h"
#include "pitEntry_m.h"

namespace inet{

class pitEntry;

class INET_API pitBase: public cSimpleModule
{
private:
    using timerTable = std::map<cMessage *, iName>;
    std::map<iName, cMessage*>* interests;

    std::multimap<iName,pitEntry>* table;

    timerTable* timers;

    fibBase *rt = nullptr;
    int interfaceId;

protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;
    void finish() override;

public:
    pitBase(const pitBase &pit) = delete;
    pitBase &operator=(const pitBase &pit) = delete;
    pitBase():cSimpleModule(){};
    // receive an iName, pit will recode it: iName,(maybe pre node name), fromIE, mac, time
    using Entry = std::pair<iName, pitEntry>;
    using EntrysRange = std::pair<std::multimap<iName, pitEntry>::iterator,
            std::multimap<iName, pitEntry>::iterator>;

    ~pitBase();
    void printPIT(std::ostream & out);
    const pitBase::Entry& createEntry(const iName& interest, const iName& nid, const MacAddress& mac,simtime_t t, int interfaceId, long Nonce = 0, bool served = false, bool is_consumer = false);
    int getInterface(){return interfaceId;}
    void addPitEntry(const Entry& entry);
    void removeEntry(const iName& interest);
    void removeEntry(const std::multimap<iName, pitEntry>::iterator);
    EntrysRange findPitEntry(const iName &interest);
    bool isConsumer(const iName& interest);
    bool servedForThisInterest(const iName &interest, unsigned long Nonce);
    bool haveThisInterest(const iName& interest){return table->find(interest) != table->end();}
    bool haveEntry(const iName& interest, long nonce);
    std::multimap<iName,pitEntry>::iterator getTableEnd(){return table->end();}
    void setServed(const iName &interest);
    void record(const pitBase::Entry &entry);
};
} //namespace inet

#endif /* INET_NETWORKLAYER_NDN_PIT_PITBASE_H_ */
