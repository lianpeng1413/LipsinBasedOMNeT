/*
 * nextHopList.cc
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/router/route/nextHopList.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"

namespace inet{
namespace nlsr {

NexthopList::NexthopList()
{
    m_nexthops = new std::vector<NextHop>;
}

NexthopList::~NexthopList()
{
    clear();
}

static bool nexthopAddCompare(const NextHop& nh1, const NextHop& nh2)
{
    return (nh1.getNextMac() == nh2.getNextMac()) &&
            (nh1.getIfIndex() == nh2.getIfIndex());
}

static bool nexthopRemoveCompare(const NextHop& nh1, const NextHop& nh2)
{
    return (nh1.getNextMac() == nh2.getNextMac() &&
            nh1.getIfIndex() == nh2.getIfIndex());
}

bool operator==(NexthopList& lhs, NexthopList& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    NexthopList slhs = lhs;
    NexthopList srhs = rhs;

    for (struct {std::set<NextHop>::iterator lItr;
    std::set<NextHop>::iterator rItr;} pair = {slhs.begin(), srhs.begin()};
        (pair.lItr != slhs.end() || pair.rItr != srhs.end());
        pair.rItr++, pair.lItr++) {
        if (!((*pair.lItr) == (*pair.rItr))) {
            return false;
        }
    }
    return true;
}

bool operator==(const NexthopList& lhs, const NexthopList& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    NexthopList slhs = lhs;
    NexthopList srhs = rhs;

    for (struct {std::set<NextHop>::iterator lItr;
    std::set<NextHop>::iterator rItr;} pair = {slhs.begin(), srhs.begin()};
        (pair.lItr != slhs.end() || pair.rItr != srhs.end());
        pair.rItr++, pair.lItr++) {
        if (!((*pair.lItr) == (*pair.rItr))) {
            return false;
        }
    }
    return true;
}

bool operator!=(const NexthopList& lhs, const NexthopList& rhs)
{
    return !(lhs == rhs);
}

//std::ostream& operator<<(std::ostream& os, const NexthopList& nhl)
//{
//    os << "  output nextHopList:  " << endl;
//
//    return os;
//}

void NexthopList::addNextHop(const NextHop& nh)
{
    auto it = std::find_if(m_nexthopList.begin(), m_nexthopList.end(),
                         std::bind(&nexthopAddCompare, std::placeholders::_1, nh));
    if (it == m_nexthopList.end()) {
        m_nexthopList.insert(nh);
    }
    else if (it->getRouteCost() > nh.getRouteCost()) {
        removeNextHop(*it);
        m_nexthopList.insert(nh);
    }
}

void NexthopList::removeNextHop(const NextHop& nh)
{
    auto it = std::find_if(m_nexthopList.begin(), m_nexthopList.end(),
                         std::bind(&nexthopRemoveCompare, std::placeholders::_1, nh));
    if (it != m_nexthopList.end()) {
        m_nexthopList.erase(it);
    }
}

//Get nextHops by interface id for routing table delete.
std::vector<NextHop>* NexthopList::getNextHops(int intf)
{
    m_nexthops->clear();
    std::map<NextHop, double> m_nexthop;
    for (auto it = m_nexthopList.begin(); it != m_nexthopList.end(); ++it){
        m_nexthop[*it] = it->getRouteCost();
    }
    for(auto it=m_nexthop.begin(); it!=m_nexthop.end(); it++){
        if(it->first.getIfIndex() == intf){
            NextHop nexthop = it->first;
            m_nexthops->push_back(nexthop);
            }
    }
    return m_nexthops;
}

// checked by yanfei 20111112
const NextHop NexthopList::getNextHop() const
{
    std::map<NextHop, double> m_nexthop;
    for (auto it = m_nexthopList.begin(); it != m_nexthopList.end(); ++it){
        m_nexthop[*it] = it->getRouteCost();
    }

    //sort MAP by value.
    std::vector<std::pair<NextHop, double>> vtMap(m_nexthop.begin(), m_nexthop.end());
    std::sort(vtMap.begin(), vtMap.end(), CmpByValue());
    NextHop nexthop = vtMap.begin()->first;
    return nexthop;  // return lowest cost.
}

} // namespace nlsr
} // namespace inet



