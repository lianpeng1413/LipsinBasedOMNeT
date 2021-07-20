/*
 * routingTablePoolEntry.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/router/route/routingTablePoolEntry.h"
#include "inet/routing/nlsr/router/route/namePrefixTableEntry.h"
#include "inet/routing/nlsr/router/route/routingTableEntry.h"

namespace inet{
namespace nlsr {

std::ostream& operator<<(std::ostream& os, RoutingTablePoolEntry& rtpe)
{
    os << "RoutingTablePoolEntry("
            << "Destination router: " << rtpe.getDestination()
            << "Next hop list: ";
    for (const auto& nh : rtpe.getNexthopList()) {
        os << nh;
    }
    os << "NamePrefixTableEntries using this entry:";
    for (const auto& entryPtr : rtpe.namePrefixTableEntries) {
        os << entryPtr.first << ":";
    }

    return os;
}

bool operator==(const RoutingTablePoolEntry& lhs, const RoutingTablePoolEntry& rhs)
{
    return (lhs.getDestination() == rhs.getDestination() && lhs.getNexthopList() == rhs.getNexthopList());
}

} // namespace nlsr
} // namespace inet



