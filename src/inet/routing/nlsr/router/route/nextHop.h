/*
 * nextHop.h
 *
 *  Created on: Aug 31, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_NEXTHOP_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_NEXTHOP_H_

#include <math.h>
#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/linklayer/common/MacAddress_m.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

namespace inet{
namespace nlsr{

class INET_API NextHop : public cObject
{
protected:
  iName nextHop;
  int ifIndex = 0;
  MacAddress nextMac;
  double routeCost = 0;

private:
  void copy(const NextHop& other);

protected:
  // protected and unimplemented operator==(), to prevent accidental usage
  bool operator==(const NextHop&);

public:
  NextHop();
  NextHop(iName& nextHopName, int interface, MacAddress& nextMac, double cost) :
        nextHop(nextHopName), ifIndex(interface), nextMac(nextMac), routeCost(cost){ }
  NextHop(const NextHop& other)
    :nextHop(other.nextHop), ifIndex(other.ifIndex), nextMac(other.nextMac), routeCost(other.routeCost){}
  virtual ~NextHop();
  NextHop& operator=(const NextHop& other);
  virtual NextHop *dup() const {return new NextHop(*this);}

  // field getter/setter methods
  virtual const iName& getNextHop() const;
  virtual iName& getNextHopForUpdate() { return const_cast<iName&>(const_cast<NextHop*>(this)->getNextHop());}
  virtual void setNextHop(const iName& nextHop);
  virtual int getIfIndex() const;
  virtual void setIfIndex(int ifIndex);
  virtual const MacAddress& getNextMac() const;
  virtual MacAddress& getNextMacForUpdate() { return const_cast<MacAddress&>(const_cast<NextHop*>(this)->getNextMac());}
  virtual void setNextMac(const MacAddress& nextMac);
  virtual double getRouteCost() const;
  virtual void setRouteCost(double routeCost);
};

bool operator==(const NextHop& lhs, const NextHop& rhs);
bool operator!=(const NextHop& lhs, const NextHop& rhs);
bool operator<(const NextHop& lhs, const NextHop& rhs);

std::ostream& operator<<(std::ostream& os, const NextHop& hop);

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_NEXTHOP_H_ */
