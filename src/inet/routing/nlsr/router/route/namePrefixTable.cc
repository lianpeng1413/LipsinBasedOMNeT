/*
 * namePrefixTable.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#include <algorithm>
#include <list>
#include <utility>

#include "inet/routing/nlsr/router/route/routingTable.h"
#include "inet/routing/nlsr/Nlsr.h"
#include "inet/routing/nlsr/router/route/namePrefixTable.h"
#include "inet/routing/nlsr/router/route/routingTableEntry.h"
#include "inet/routing/nlsr/router/route/fib.h"

namespace inet{
namespace nlsr {

NamePrefixTable::NamePrefixTable(Fib *fib, RoutingTable *rt):
        m_fib(fib),
        m_routingTable(rt)
{
}

NamePrefixTable::~NamePrefixTable()
{
}

void NamePrefixTable::addEntry(const iName& name, const iName& destRouter)
{
    EV_INFO << "Updating FIB with next hops " << endl;
    // Check if the advertised name prefix is in the table already.
    NptEntryList::iterator nameItr = std::find_if(m_table.begin(), m_table.end(),
                 [&] (const std::shared_ptr<NamePrefixTableEntry>& entry) {
                   return name == entry->getNamePrefix();});

    // Attempt to find a routing table pool entry (RTPE) we can use.
    RoutingTableEntryPool::iterator rtpeItr = m_rtpool.find(destRouter);

    // These declarations just to make the compiler happy...
    RoutingTablePoolEntry rtpe;
    std::shared_ptr<RoutingTablePoolEntry> rtpePtr(nullptr);

    // There isn't currently a routing table entry in the pool for this name
    if (rtpeItr == m_rtpool.end()) {
        // See if there is a routing table entry available we could use
        RoutingTableEntry* routeEntryPtr = m_routingTable->findRoutingTableEntry(destRouter);

        // We have to create a new routing table entry
        if (routeEntryPtr == nullptr) {
            rtpe = RoutingTablePoolEntry(destRouter, 0);
        }
        // There was already a usable one in the routing table
        else {
            rtpe = RoutingTablePoolEntry(*routeEntryPtr, 0);
        }

        // Add the new pool object to the pool.
        rtpePtr = addRtpeToPool(rtpe);
    }
    // There was one already, so just fetch that one.
    else {
        rtpePtr = (*rtpeItr).second;
    }

    std::shared_ptr<NamePrefixTableEntry> npte;
    // Either we have to make a new NPT entry or there already was one.
    if (nameItr == m_table.end()) {
        EV_INFO << "Adding origin: " << rtpePtr->getDestination()
               << " to a new name prefix: " << name.str() << endl;
        npte = std::make_shared<NamePrefixTableEntry>(name);
        npte->addRoutingTableEntry(rtpePtr);
        npte->generateNhlfromRteList();
        m_table.push_back(npte);
        // If this entry has next hops, we need to inform the FIB
        if (npte->getNexthopList().size() > 0) {
            EV_INFO << "Updating FIB with next hops for " << npte->getNamePrefix() << endl;
            m_fib->update(name, npte->getNexthopList());
        }
        // The routing table may recalculate and add a routing table entry
        // with no next hops to replace an existing routing table entry. In
        // this case, the name prefix is no longer reachable through a next
        // hop and should be removed from the FIB. But, the prefix should
        // remain in the Name Prefix Table as a future routing table
        // calculation may add next hops.
        else {
            EV_INFO << npte->getNamePrefix() << " has no next hops; removing from FIB" << endl;
            m_fib->remove(name);
        }
    }
    else {
        npte = *nameItr;
        EV_INFO << "Adding origin: " << rtpePtr->getDestination() <<
                   " to existing prefix: " << **nameItr << endl;
        (*nameItr)->addRoutingTableEntry(rtpePtr);
        (*nameItr)->generateNhlfromRteList();

        if ((*nameItr)->getNexthopList().size() > 0) {
            EV_INFO << "Updating FIB with next hops for " << (**nameItr) << endl;
            m_fib->update(name, (*nameItr)->getNexthopList());
        }
        else {
            EV_INFO << npte->getNamePrefix() << " has no next hops; removing from FIB" << endl;
            m_fib->remove(name);
        }
    }
    // Add the reference to this NPT to the RTPE.
    rtpePtr->namePrefixTableEntries.emplace(
            std::make_pair(npte->getNamePrefix(), std::weak_ptr<NamePrefixTableEntry>(npte)));
}

void NamePrefixTable::removeEntry(const iName& name, const iName& destRouter)
{
    EV_INFO << "Removing origin: " << destRouter << " from " << name <<endl;

    // Fetch an iterator to the appropriate pair object in the pool.
    RoutingTableEntryPool::iterator rtpeItr = m_rtpool.find(destRouter);

    // Simple error checking to prevent any unusual behavior in the case
    // that we try to remove an entry that isn't there.
    if (rtpeItr == m_rtpool.end()) {
        EV_INFO << "No entry for origin: " << destRouter
               << " found, so it cannot be removed from prefix: " << name << endl;
        return;
    }
    std::shared_ptr<RoutingTablePoolEntry> rtpePtr = rtpeItr->second;

    // Ensure that the entry exists
    NptEntryList::iterator nameItr = std::find_if(m_table.begin(), m_table.end(),
                 [&] (const std::shared_ptr<NamePrefixTableEntry>& entry) {
                   return entry->getNamePrefix() == name; });
    if (nameItr != m_table.end()) {
        EV_INFO << "Removing origin: " << rtpePtr->getDestination()
               << " from prefix: " << **nameItr << endl;

        // Rather than iterating through the whole list periodically, just
        // delete them here if they have no references.
        if ((*nameItr)->removeRoutingTableEntry(rtpePtr) == 0) {
            deleteRtpeFromPool(rtpePtr);
        }

        // If the prefix is a router prefix and it does not have any other
        // routing table entries, the Adjacency/Coordinate LSA associated
        // with that origin router has been removed from the LSDB and so
        // the router prefix should be removed from the Name Prefix Table.
        //
        // If the prefix is an advertised name prefix: If another router
        //   advertises this name prefix, the RteList should have another
        //   entry for that router; the next hops should be recalculated
        //   and installed in the FIB.
        //
        //   If no other router advertises this name prefix, the RteList
        //   should be empty and the prefix can be removed from the Name
        //   Prefix Table. Once a new Name LSA advertises this prefix, a
        //   new entry for the prefix will be created.

        if ((*nameItr)->getRteListSize() == 0) {
            EV_INFO << **nameItr << " has no routing table entries;"
                    << " removing from table and FIB" <<endl;
            m_table.erase(nameItr);
            m_fib->remove(name);
        }
        else {
            EV_INFO << **nameItr << " has other routing table entries;"
                    << " updating FIB with next hops" << endl;
            (*nameItr)->generateNhlfromRteList();
            m_fib->update(name, (*nameItr)->getNexthopList());
        }
    }
    else {
        EV_INFO << "Attempted to remove origin: " << rtpePtr->getDestination()
                << " from non-existent prefix: " << name << endl;
    }
}

void NamePrefixTable::updateWithNewRoute(const std::list<RoutingTableEntry>& entries)
{
    // Iterate over each pool entry we have
    for (auto& poolEntryPair : m_rtpool) {
        auto&& poolEntry = poolEntryPair.second;
        auto sourceEntry = std::find_if(entries.begin(), entries.end(),
                                    [&poolEntry] (const RoutingTableEntry& entry) {
                                      return poolEntry->getDestination() == entry.getDestination();
                                    });
        // If this pool entry has a corresponding entry in the routing table now
        if (sourceEntry != entries.end()
                && poolEntry->getNexthopList() != sourceEntry->getNexthopList()) {
            EV_INFO << "Routing entry: " << poolEntry->getDestination() << " has changed next-hops." << endl;
            poolEntry->setNexthopList(sourceEntry->getNexthopList());
            for (const auto& nameEntry : poolEntry->namePrefixTableEntries) {
                auto nameEntryFullPtr = nameEntry.second;
                addEntry(nameEntryFullPtr->getNamePrefix(), poolEntry->getDestination());
            }
        }
        else if (sourceEntry == entries.end()) {
            EV_INFO << "Routing entry: " << poolEntry->getDestination() << " now has no next-hops." <<endl;
            poolEntry->getNexthopListForUpdate().clear();
            for (const auto& nameEntry : poolEntry->namePrefixTableEntries) {
                auto nameEntryFullPtr = nameEntry.second;
                addEntry(nameEntryFullPtr->getNamePrefix(), poolEntry->getDestination());
            }
        }
        else {
            EV_INFO << "No change in routing entry:" << poolEntry->getDestination()
                    << ", no action necessary." << endl;
        }
    }
    }

// Inserts the routing table pool entry into the NPT's RTE storage pool.
//This cannot fail, so the pool is guaranteed to contain the item after this occurs.
std::shared_ptr<RoutingTablePoolEntry> NamePrefixTable::addRtpeToPool(RoutingTablePoolEntry& rtpe)
{
    RoutingTableEntryPool::iterator poolItr = m_rtpool.insert(std::make_pair(rtpe.getDestination(),
                                    std::make_shared<RoutingTablePoolEntry> (rtpe))).first;
    return poolItr->second;
}

// Removes the routing table pool entry from the storage pool. The
// postconditions of this function are guaranteed to include that
// the storage pool does not contain such an item. Additionally,
// this function cannot fail, but nonetheless debug information is
// given in the case that this function is called with an entry that isn't in the pool.
void NamePrefixTable::deleteRtpeFromPool(std::shared_ptr<RoutingTablePoolEntry> rtpePtr)
{
    if (m_rtpool.erase(rtpePtr->getDestination()) != 1) {
        EV_INFO << "Attempted to delete non-existent origin: "
                << rtpePtr->getDestination()
                << " from NPT routing table entry storage pool." << endl;
    }
}

std::ostream& operator<<(std::ostream& os, const NamePrefixTable& table)
{
    os << "----------------NPT----------------------\n";

    for (const auto& entryPtr : table) {
        os << *entryPtr << std::endl;
    }

    return os;
}

} // namespace nlsr
} // namespace inet



