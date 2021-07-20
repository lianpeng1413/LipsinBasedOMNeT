/*
 * routingTablePoolEntry.h
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLEPOOLENTRY_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLEPOOLENTRY_H_

#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/linklayer/common/MacAddress.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/nlsr/router/route/nextHopList.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/router/route/routingTableEntry.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"

namespace inet {
namespace nlsr {

/*!A deduplication system for the NamePrefixTable
 *
 * The NamePrefixTable associates name prefixes to a router. To do
 * this, it needs to know if certain routers are reachable. This in
 * turn requires access to entries from the RoutingTable, which are
 * associated with name prefixes. Doing this naively copies the entry
 * from the RoutingTable each time, which is costly. This class
 * provides a deduplication system where the NamePrefixTable can
 * maintain a collection of RoutingTablePoolEntries. Then, this new
 * class can be associated with the name prefixes instead of the
 * original entries. */
class NamePrefixTableEntry;

class RoutingTablePoolEntry : public RoutingTableEntry
{
private:
    long m_useCount;

public:
    std::map<iName, std::shared_ptr<NamePrefixTableEntry>> namePrefixTableEntries;

public:
    RoutingTablePoolEntry() { }

     ~RoutingTablePoolEntry() { }

     RoutingTablePoolEntry(const iName& dest)
     {
       destination = dest;
       m_useCount = 1;
     }

     RoutingTablePoolEntry(RoutingTableEntry& rte, uint64_t useCount)
     {
       destination = rte.getDestination();
       nexthopList = rte.getNexthopList();
       m_useCount = useCount;
     }

     RoutingTablePoolEntry(const iName& dest, uint64_t useCount)
     {
       destination = dest;
       m_useCount = useCount;
     }

    long getUseCount() { return m_useCount; }
    long incrementUseCount() { return ++m_useCount; }

    long decrementUseCount()
    {
        if (m_useCount != 0) {
            return --m_useCount;
        }
        return 0;
    }

    void setNexthopList(NexthopList nhl) { nexthopList = nhl; }
};

bool operator==(const RoutingTablePoolEntry& lhs, const RoutingTablePoolEntry& rhs);

std::ostream& operator<<(std::ostream& os, RoutingTablePoolEntry& rtpe);

} // namespace nlsr
} // namespace inet




#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLEPOOLENTRY_H_ */
