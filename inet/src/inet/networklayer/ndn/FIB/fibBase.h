/*
 * fibBase.h
 *
 *  Created on: Oct 10, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_NDN_FIB_FIBBASE_H_
#define INET_NETWORKLAYER_NDN_FIB_FIBBASE_H_

#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/networklayer/ndn/FIB/iFib_m.h"

namespace inet{

class iFib;
using std::shared_ptr;
using std::unique_ptr;
class fibBase : public cSimpleModule
{
    private:
        using Table = std::multimap<iName, std::shared_ptr<iFib>>;

        Table fib;

        bool isNodeUp;
        bool forwarding = false;

        fibBase(const fibBase&);
        fibBase& operator = (const fibBase);
    public:
        fibBase(){}
        ~fibBase();
        void CreateEntry(const iName& dest, const iName& nextHop, const MacAddress& mac, const simtime_t& ttl, int interFace, double linkQ );
        void printRoutingTable(std::ostream & out);
        cModule *getHostModule();
        shared_ptr<iFib> findRoute(iName dest);
        void removeEntry(iName nid);
    protected:
        virtual void handleMessage(cMessage *)override;
        virtual int numInitStages() const override { return NUM_INIT_STAGES; }
        virtual void initialize(int stage) override;
};
}



#endif /* INET_NETWORKLAYER_NDN_FIB_FIBBASE_H_ */
