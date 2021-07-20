/*
 * routingTableEntry.h
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLEENTRY_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLEENTRY_H_

#include <map>
#include <memory>
#include <iostream>
#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/linklayer/common/MacAddress.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/IRoute.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/router/route/nextHopList.h"

namespace inet {
namespace nlsr {

//class RoutingTableEntry : public cObject
class RoutingTableEntry
{
protected:
    iName destination;
    NexthopList nexthopList;
private:
    void copy(const RoutingTableEntry& other);

public:
    RoutingTableEntry();
    ~RoutingTableEntry();

    //??Do we need addNextHop, set actions?
    RoutingTableEntry(const iName& dest):destination(dest){}

    RoutingTableEntry(const RoutingTableEntry& entry):
            destination(entry.destination), nexthopList(entry.nexthopList){}

    RoutingTableEntry& operator=(const RoutingTableEntry& other);
    RoutingTableEntry *dup() const {return new RoutingTableEntry(*this);}

    // field getter/setter methods
    virtual const iName& getDestination() const;
    virtual iName& getDestinationForUpdate() { return const_cast<iName&>(const_cast<RoutingTableEntry*>(this)->getDestination());}
    virtual void setDestination(const iName& destination);
    virtual const NexthopList& getNexthopList() const;
    NexthopList& getNexthopList() { return nexthopList; }
    virtual NexthopList& getNexthopListForUpdate() { return const_cast<NexthopList&>(const_cast<RoutingTableEntry*>(this)->getNexthopList());}
    virtual void setNexthopList(const NexthopList& nexthopList);

    inline bool operator==(RoutingTableEntry& rhs)
    {
        return destination == rhs.getDestination() &&
                nexthopList == rhs.getNexthopList();
    }

    bool comparator(RoutingTableEntry& c1, RoutingTableEntry& c2);
};

//std::ostream& operator<<(std::ostream& os, const RoutingTableEntry& rte);

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLEENTRY_H_ */
