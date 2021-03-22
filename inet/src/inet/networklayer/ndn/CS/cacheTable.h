/*
 * cacheTable.h
 *
 *  Created on: Oct 1, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_NDN_CS_CACHETABLE_H_
#define INET_NETWORKLAYER_NDN_CS_CACHETABLE_H_

#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <queue>
#include <vector>
#include <list>

#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/networklayer/ndn/CS/contentBlock.h"

namespace inet
{
class contentBlock;
using std::shared_ptr;

struct INameCompare
{
    bool operator ()(const iName &lhs, const iName &rhs)
    {
        return lhs.str() < rhs.str();
    }
};

class INET_API cacheTable : public cSimpleModule, protected cListener, public ILifecycle
{
private:
    using CacheTable = std::map<iName, shared_ptr<contentBlock>,INameCompare>;
    using timerTable = std::map<cMessage *, iName>;

    CacheTable table;
    cModule *owner;
    timerTable *timers; //for every interest item
    unsigned mtu;
    bool isNodeUp;
    B size;   //content store size
    B remain;  // remained storage

public:
    cacheTable(){}
    ~cacheTable(){};

    // forbidden copy and mutator
    cacheTable(const cacheTable &) = delete;
    cacheTable &operator = (const cacheTable) = delete;
    void setOwer(cModule *own) { owner = own;}
    void printCacheTable(std::ostream &out);

    // return interest and create block
    shared_ptr<contentBlock> getBlock(const iName &interest);
    shared_ptr<contentBlock> createBlock(const iName &interest);

    void cachePacket(const iName &interestName, Packet *packet);
    void removeBlock(shared_ptr<contentBlock> block);
    bool hasThisPacket(Packet *packet, const iName &interest);
    void clear();

protected:
    void finish() override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual cModule *getHostModule() { return owner; }
    virtual void handleMessage (cMessage *) override;
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;
    virtual bool handleOperationStage(LifecycleOperation * operation, IDoneCallback *doneCallback) override;
};
}
#endif /* INET_NETWORKLAYER_NDN_CS_CACHETABLE_H_ */
