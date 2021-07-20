/*
 * routingTable.h
 *
 *  Created on: Sep 4, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLE_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLE_H_

#include <memory.h>

#include "fib.h"
#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/nlsr/router/route/routingTableEntry.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet{
namespace nlsr {

class Router;
class NextHop;
class routingTableEntry;
class NamePrefixTable;

using std::shared_ptr;
using std::unique_ptr;

class INET_API RoutingTableStatus
{
private:
//    std::vector<RoutingTableEntry> m_dryTable;
//    std::vector<RoutingTableEntry> m_rTable;
public:
    RoutingTableStatus() = default;
//    const std::list<RoutingTableEntry>& getRoutingTableEntry() const { return m_rTable; }
//    const std::list<RoutingTableEntry>& getDryRoutingTableEntry() const { return m_dryTable; }
};
//std::ostream& operator<<(std::ostream& os, const RoutingTableStatus& rts);

class INET_API RoutingTable : public RoutingTableStatus, public cSimpleModule, protected cListener, public ILifecycle
{
private:
    NlsrArea* m_lsdb;
//    NamePrefixTable* m_namePrefixTable;
    NlsrInterface* interface;
    std::list<RoutingTableEntry> m_dryTable;
    std::list<RoutingTableEntry> m_rTable;

protected:
    IInterfaceTable *ift = nullptr;    // cached pointer
    RouterName routerId;
    bool forwarding = false;
    bool isNodeUp = false;
    std::string path; //used for saving routing convergence results.

public:
//    /**
//     * Sent a routing update signal
//     */
//    class routingChanged : public cObject
//    {
//      public:
//        std::list<RoutingTableEntry> entries;
//
//      public:
//        routingChanged(std::list<RoutingTableEntry>& m_Entries)
//            : entries(m_Entries){}
//    };
//
//    /** @brief Signals used to inform routing changed. */
//    static const simsignal_t routingChangedSignal;

    const std::list<RoutingTableEntry>& getRoutingTableEntry() const { return m_rTable; }
    const std::list<RoutingTableEntry>& getDryRoutingTableEntry() const { return m_dryTable; }

public:
    //return the pointer of host node
    cModule *getHostModule();

//    explicit RoutingTable(Router* lsdb, NamePrefixTable& namePrefixTable);
    RoutingTable(){}
    ~RoutingTable();
    uint64_t getRtSize(){ return m_rTable.size(); }

    /*! Calculates a list of next hops for each router in the network.  */
    void calculate();

    /*! Adds a next hop to a routing table entry. */
    void addNextHop(const iName& destRouter, NextHop& nh);

    /*! Adds a next hop to a routing table entry in a dry run scenario.*/
    void addNextHopToDryTable(const iName& destRouter, NextHop& nh);

    RoutingTableEntry* findRoutingTableEntry(const iName& destRouter);

    /**For debugging */
//    virtual void printRoutingTable() const override;

    /*! \brief Calculates a link-state routing table. */
    void calculateLsRoutingTable();

    void clearRoutingTable();

    void clearDryRoutingTable();

    void setArea(NlsrArea *area) { m_lsdb = area; }

    std::list<RoutingTableEntry>& getRoutingTable();

    /** Returns routerId.  */
    RouterName getRouterId() const { return routerId; }

    /** Sets routerId. */
    void setRouterId(RouterName a) { routerId = a; }

    /** Removes the given route from the routing table, and returns it.
     * nullptr is returned of the route was not in the routing table.  */
    shared_ptr<routingTableEntry> removeRoute(iName name);

    /**To be called from route objects whenever a field changes. Used for maintaining internal
     * data structures and firing "routing table changed notifications. */
    shared_ptr<routingTableEntry> routeChanged(iName *name);

    /** ILifecycle method. */
    virtual bool handleOperationStage(LifecycleOperation *operation, IDoneCallback *doneCallback) override;

protected:
    virtual void handleMessage(cMessage *)override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    /**! Called by the signal handler whenever a change of a category
     * occurs to which this client has subscribed.  */
//    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

};
} // namespace nlsr
} //namespace inet


#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLE_H_ */
