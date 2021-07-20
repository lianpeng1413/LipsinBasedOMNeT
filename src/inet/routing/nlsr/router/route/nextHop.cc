/*
 * nextHop.cc
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */
#include <iostream>
#include <sstream>
#include <memory>

#include "nextHop.h"

namespace inet{
namespace nlsr{

NextHop::NextHop()
{
}

NextHop::~NextHop()
{
}

NextHop& NextHop::operator=(const NextHop& other)
{
    if (this == &other) return *this;

    else{
        this->ifIndex = other.ifIndex;
        this->nextHop = other.nextHop;
        this->nextMac = other.nextMac;
        this->routeCost = other.routeCost;
        return *this;
    }
}

const iName& NextHop::getNextHop() const
{
    return this->nextHop;
}

void NextHop::setNextHop(const iName& nextHop)
{
    this->nextHop = nextHop;
}

int NextHop::getIfIndex() const
{
    return this->ifIndex;
}

void NextHop::setIfIndex(int ifIndex)
{
    this->ifIndex = ifIndex;
}

const MacAddress& NextHop::getNextMac() const
{
    return this->nextMac;
}

void NextHop::setNextMac(const MacAddress& nextMac)
{
    this->nextMac = nextMac;
}

double NextHop::getRouteCost() const
{
    return this->routeCost;
}

void NextHop::setRouteCost(double routeCost)
{
    this->routeCost = routeCost;
}
//simtime_t NextHop::getLifeTime() const
//{
//    this->lifeTime;
//}
//void NextHop::setLifeTime(simtime_t lTime)
//{
//    this->lifeTime = lTime;
//}

// compare two nextHop.
bool operator==(const NextHop& lhs, const NextHop& rhs)
{
  return (lhs.getIfIndex() == rhs.getIfIndex()) &&
         (lhs.getNextHop() == rhs.getNextHop()) &&
         (lhs.getNextMac() == rhs.getNextMac());
}

bool operator!=(const NextHop& lhs, const NextHop& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const NextHop& lhs, const NextHop& rhs)
{
    if( (lhs.getNextHop() == rhs.getNextHop()) && (lhs.getRouteCost() < rhs.getRouteCost()))
        return true;
    else
        return false;
}

std::ostream& operator<<(std::ostream& os, const NextHop& hop)
{
    os << "NextHop(interfaceIndex: " << hop.getIfIndex()
       << "nextHop: " << hop.getNextHop()
       << "nextMac: " << hop.getNextMac()
       << "Cost: " << hop.getRouteCost() << ")";
    return os;
}
} // namespace nlsr
} // namespace inet


