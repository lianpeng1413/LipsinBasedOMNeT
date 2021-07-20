/*
 * namePrefixTable.h
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_NAMEPREFIXTABLE_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_NAMEPREFIXTABLE_H_

#include <list>
#include <unordered_map>

#include "inet/routing/nlsr/router/route/namePrefixTableEntry.h"
#include "inet/routing/nlsr/router/route/routingTablePoolEntry.h"

namespace inet {
namespace nlsr {

class RoutingTable;
class Fib;
using std::shared_ptr;

class NamePrefixTable
{
public:
    using RoutingTableEntryPool = std::unordered_map<iName, shared_ptr<RoutingTablePoolEntry>>;
    using NptEntryList = std::vector<shared_ptr<NamePrefixTableEntry>>;
    using const_iterator = NptEntryList::const_iterator;

private:
    RoutingTableEntryPool m_rtpool;
    NptEntryList m_table;
    Fib* m_fib = nullptr;
    RoutingTable* m_routingTable = nullptr;

public:
    //?? name prefix table must be changed after routing table changed.(in routing table to trigger update.)
    NamePrefixTable(Fib *fib, RoutingTable *rt);
    ~NamePrefixTable();

    /*! Adds a destination to the specified name prefix.   */
    void addEntry(const iName& name, const iName& destRouter);

    /*! Removes a destination from a name prefix table entry.  */
    void removeEntry(const iName& name, const iName& destRouter);

    /*! Updates all routing information in the NPT. */
    void updateWithNewRoute(const std::list<RoutingTableEntry>& entries);

    /*! Adds a pool entry to the pool.  */
    std::shared_ptr<RoutingTablePoolEntry> addRtpeToPool(RoutingTablePoolEntry& rtpe);

    /*! Removes a pool entry from the pool.  */
    void deleteRtpeFromPool(std::shared_ptr<RoutingTablePoolEntry> rtpePtr);

    const_iterator begin() const;
    const_iterator end() const;
};

inline NamePrefixTable::const_iterator NamePrefixTable::begin() const
{
  return m_table.begin();
}

inline NamePrefixTable::const_iterator NamePrefixTable::end() const
{
  return m_table.end();
}

std::ostream& operator<<(std::ostream& os, const NamePrefixTable& table);

} // namespace nlsr
} // namespace inet



#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_NAMEPREFIXTABLE_H_ */
