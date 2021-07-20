/*
 * fib.h
 *
 *  Created on: Nov 11, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_FIB_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_FIB_H_

#include <map>
#include <memory>
#include <iostream>
#include <vector>

#include "inet/routing/nlsr/neighbor/adjacencyList.h"
#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/linklayer/common/MacAddress_m.h"
#include "inet/routing/nlsr/router/route/nextHopList.h"

namespace inet{
namespace nlsr{

class FibEntry;
using std::shared_ptr;
using std::unique_ptr;

typedef std::function<void(FibEntry&)> afterRefreshCallback;

/*! Maps names to lists of next hops.FIB (Forwarding Information Base) is the "authoritative"
 * source of how to route Interests on this router to other nodes running NLSR.  */

class INET_API Fib : public cSimpleModule
{
private:
    AdjacencyList* m_adjacencyList = nullptr;
//    static const std::string MULTICAST_STRATEGY;
//    static const std::string BEST_ROUTE_V2_STRATEGY;

    using Table = std::map<iName, std::shared_ptr<FibEntry>>;
    Table fib;
    bool isNodeUp;
    bool forwarding = true;

public:
    Fib(const Fib &obj) = delete;
    Fib &operator=(const Fib &obj) = delete;
    Fib():cSimpleModule(){}
    ~Fib();
    cModule *getHostModule();   // get host module

    void setAdjList(AdjacencyList* adjList) { m_adjacencyList = adjList; }

    /*!Set the nexthop list of a name.  */
    void update(const iName& name, const NexthopList& allHops);

    shared_ptr<FibEntry> lookup(const iName& name); //find out

    /*! Completely remove a name prefix from the FIB.  */
    void remove(const iName& name);

    void updateNextHop(int intf);

    /*! Remove all entries from the FIB.  */
    void clean();

    /*! \brief Inform NFD of a next-hop. ??? TODO */
    void registerPrefix(const iName& namePrefix, int ifIndex, double faceCost, simtime_t times);

    /*! Does one half of the updating of a FibEntry with new next-hops. */
    void addNextHopsToFibEntry(const iName& name, std::shared_ptr<FibEntry> entry, const NexthopList& hopsToAdd);

    /*!Indicates whether a prefix is a direct neighbor or not. */
    bool isNotNeighbor(const iName& name);
    unsigned int getNumberOfFacesForName(const NexthopList& nextHopList);

protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;
    void finish() override;
 };

 }  // namespace nlsr
 }  // namespace inet


#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_FIB_H_ */
