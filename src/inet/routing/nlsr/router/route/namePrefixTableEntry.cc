/*
 * namePrefixTableEntry.cc
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */

#include <algorithm>
#include <list>
#include <utility>

#include "inet/routing/nlsr/router/route/namePrefixTable.h"
#include "inet/routing/nlsr/router/route/namePrefixTableEntry.h"
#include "inet/routing/nlsr/router/route/routingTable.h"
#include "inet/routing/nlsr/Nlsr.h"
#include "inet/routing/nlsr/router/route/nextHop.h"

namespace inet{
namespace nlsr {

void NamePrefixTableEntry::generateNhlfromRteList()
{
    m_nexthopList.clear();
    for (auto iterator = m_rteList.begin(); iterator != m_rteList.end(); ++iterator) {
        for (auto nhItr = (*iterator)->getNexthopList().getNextHops().begin();
                nhItr != (*iterator)->getNexthopList().getNextHops().end();
                ++nhItr) {
            m_nexthopList.addNextHop((*nhItr));
        }
    }
}

int NamePrefixTableEntry::removeRoutingTableEntry(std::shared_ptr<RoutingTablePoolEntry> entryPtr)
{
    auto iterator = std::find(m_rteList.begin(), m_rteList.end(), entryPtr);

    if (iterator != m_rteList.end()) {
        (*iterator)->decrementUseCount();
        // Remove this NamePrefixEntry from the RoutingTablePoolEntry
        (*iterator)->namePrefixTableEntries.erase(getNamePrefix());
        m_rteList.erase(iterator);
    }
    else {
        EV_INFO << "Routing entry for: " << entryPtr->getDestination()
               << " not found in NPT entry: " << getNamePrefix() << endl;
    }
    return entryPtr->getUseCount();
}

void NamePrefixTableEntry::addRoutingTableEntry(std::shared_ptr<RoutingTablePoolEntry> entryPtr)
{
    auto iterator = std::find(m_rteList.begin(), m_rteList.end(), entryPtr);

    // Ensure that this is a new entry
    if (iterator == m_rteList.end()) {
        // Adding a new routing entry to the NPT entry
        entryPtr->incrementUseCount();
        m_rteList.push_back(entryPtr);
    }
}

bool operator==(const NamePrefixTableEntry& lhs, const NamePrefixTableEntry& rhs)
{
    return lhs.getNamePrefix() == rhs.getNamePrefix();
}

bool operator==(const NamePrefixTableEntry& lhs, const iName& rhs)
{
    return lhs.getNamePrefix() == rhs;
}

std::ostream& operator<<(std::ostream& os, const NamePrefixTableEntry& entry)
{
    os << "Name: " << entry.getNamePrefix().str() << "\n";

    for (const auto& entryPtr : entry.getRteList()) {
        os << "  Destination: " << entryPtr->getDestination().str() << "\n";
//        os << entryPtr->getNexthopList();
    }
    return os;
}

} // namespace nlsr
} // namespace inet



