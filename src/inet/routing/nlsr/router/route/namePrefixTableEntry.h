/*
 * namePrefixTableEntry.h
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_NAMEPREFIXTABLEENTRY_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_NAMEPREFIXTABLEENTRY_H_

#include <list>
#include <utility>
#include <map>
#include <memory>
#include <iostream>
#include <vector>

#include "../../neighbor/adjacencyList.h"
#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

#include "inet/routing/nlsr/router/route/fibEntry_m.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/linklayer/common/MacAddress_m.h"
#include "inet/routing/nlsr/router/route/nextHopList.h"
#include "inet/routing/nlsr/router/route/routingTablePoolEntry.h"

namespace inet{
namespace nlsr {

class NamePrefixTableEntry
{
private:
    iName m_namePrefix;
    std::list<std::shared_ptr<RoutingTablePoolEntry>> m_rteList;
    NexthopList m_nexthopList;

public:
  NamePrefixTableEntry() { }

  NamePrefixTableEntry(const iName& namePrefix): m_namePrefix(namePrefix), m_nexthopList(){}

  const iName& getNamePrefix() const { return m_namePrefix; }

  const std::list<std::shared_ptr<RoutingTablePoolEntry>>& getRteList() const
  {
    return m_rteList;
  }

  /*!Resets the next hop lists of all routing table entries that advertise this name prefix.*/
  void resetRteListNextHop()
  {
    if (m_rteList.size() > 0) {
      for (auto it = m_rteList.begin(); it != m_rteList.end(); ++it) {
        (*it)->getNexthopListForUpdate().clear();
      }
    }
  }

  int getRteListSize() { return m_rteList.size(); }

  const NexthopList& getNexthopList() const { return m_nexthopList; }

  /*! Collect all next-hops that are advertised by this entry'srouting entries. */
  void generateNhlfromRteList();

  /*! Removes a routing entry from this NPT entry. */
  int removeRoutingTableEntry(std::shared_ptr<RoutingTablePoolEntry> rtpePtr);

  /*!Adds a routing entry to this NPT entry. Adds a routing table pool entry to this NPT
   * entry's list.  */
  void addRoutingTableEntry(std::shared_ptr<RoutingTablePoolEntry> rtpePtr);

};

bool operator==(const NamePrefixTableEntry& lhs, const NamePrefixTableEntry& rhs);

bool operator==(const NamePrefixTableEntry& lhs, const iName& rhs);

std::ostream& operator<<(std::ostream& os, const NamePrefixTableEntry& entry);

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_NAMEPREFIXTABLEENTRY_H_ */
