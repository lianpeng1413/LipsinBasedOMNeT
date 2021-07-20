/*
 * routingTableEntry.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/router/route/routingTableEntry.h"
#include "inet/routing/nlsr/router/route/nextHopList.h"

namespace inet {
namespace nlsr {

RoutingTableEntry::RoutingTableEntry(){}

RoutingTableEntry::~RoutingTableEntry(){}

RoutingTableEntry& RoutingTableEntry::operator=(const RoutingTableEntry& other)
{
    if (this == &other) return *this;
//    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void RoutingTableEntry::copy(const RoutingTableEntry& other)
{
    this->destination = other.destination;
    this->nexthopList = other.nexthopList;
}

const iName& RoutingTableEntry::getDestination() const
{
    return this->destination;
}

void RoutingTableEntry::setDestination(const iName& destination)
{
    this->destination = destination;
}

const NexthopList& RoutingTableEntry::getNexthopList() const
{
    return this->nexthopList;
}

void RoutingTableEntry::setNexthopList(const NexthopList& nexthopList)
{
    this->nexthopList = nexthopList;
}


bool RoutingTableEntry::comparator(RoutingTableEntry&c1, RoutingTableEntry& c2)
{
    if(c1.getNexthopList() == c2.getNexthopList())
        return true;
    else
        return false;
}
//std::ostream& operator<<(std::ostream& os, const RoutingTableEntry& rte)
//{
//    os << "  Destination: " << rte.getDestination() << "\n"
//            << rte.getNexthopList() << "\n";
//
//    return os;
//}

} // namespace nlsr
} // namespace inet


