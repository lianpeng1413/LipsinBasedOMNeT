/*
 * nextHopList.h
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_NEXTHOPLIST_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_NEXTHOPLIST_H_

#include <math.h>
#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/linklayer/common/MacAddress_m.h"
#include "inet/routing/nlsr/router/route/nextHop.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"

namespace inet{
namespace nlsr{

struct NextHopComparator {
  bool operator() (const NextHop& nh1, const NextHop& nh2) const {
    if (nh1.getRouteCost()< nh2.getRouteCost()) {
      return true;
    }
    else if (nh1.getRouteCost() == nh2.getRouteCost()) {
      return nh1.getIfIndex() < nh2.getIfIndex();
    }
    else {
      return false;
    }
  }
};

struct CmpByValue {
  bool operator()(const std::pair<NextHop, double> & lhs, const std::pair<NextHop, double> & rhs)
  {return lhs.second < rhs.second;}
};

class NexthopList
{
private:
    std::set<NextHop, NextHopComparator> m_nexthopList;
    std::vector<NextHop>* m_nexthops;

public:
    NexthopList();
    virtual ~NexthopList();

    NexthopList(const NexthopList& entry): m_nexthopList(entry.m_nexthopList){}

    /*!Adds a next hop to the list.
     *Function: Adds a next hop to this object. If the next hop is new it is added.
      If the next hop already exists in the list then that next hop's route cost is updated.
    */
    void addNextHop(const NextHop& nh);

    /*!Remove a next hop from the Next Hop list.
       The next hop gets removed only if both next hop interface, MAC and route cost are same.
    */
    void removeNextHop(const NextHop& nh);

    size_t size() const {  return m_nexthopList.size(); }

    void clear() { m_nexthopList.clear(); }

    const std::set<NextHop, NextHopComparator>& getNextHops() const
    {
      return m_nexthopList;
    }

    std::vector<NextHop>* getNextHops(int intf);
    const NextHop getNextHop() const;

    typedef std::set<NextHop, NextHopComparator>::iterator iterator;
    typedef std::set<NextHop, NextHopComparator>::const_iterator const_iterator;
    typedef std::set<NextHop, NextHopComparator>::reverse_iterator reverse_iterator;

    iterator begin() { return m_nexthopList.begin(); }

    iterator end() { return m_nexthopList.end(); }

    const_iterator cbegin() const { return m_nexthopList.begin(); }

    const_iterator cend() const { return m_nexthopList.end(); }

    reverse_iterator rbegin() const  { return m_nexthopList.rbegin(); }

    reverse_iterator rend() const { return m_nexthopList.rend(); }

};

bool operator==(NexthopList& lhs, NexthopList& rhs);

bool operator==(const NexthopList& lhs, const NexthopList& rhs);

bool operator!=(const NexthopList& lhs, const NexthopList& rhs);

//std::ostream& operator<<(std::ostream& os, const NexthopList& nhl);

} // namespace nlsr
} // namespace inet
#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_NEXTHOPLIST_H_ */
