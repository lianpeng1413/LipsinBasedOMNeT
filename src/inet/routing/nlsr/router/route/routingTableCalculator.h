/*
 * routingTableCalculator.h
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLECALCULATOR_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLECALCULATOR_H_

#include <list>
#include <algorithm>
#include <sstream>
#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/PatternMatcher.h"
#include "inet/common/Simsignals.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/router/route/map.h"
#include "inet/routing/nlsr/router/route/routingTable.h"

namespace inet{
namespace nlsr {

class Map;
class RoutingTable;
class Router;

class RoutingTableCalculator
{
protected:
    double** adjMatrix;
    size_t m_nRouters;

    int vNoLink;
    int* links;
    double* linkCosts;

public:
    RoutingTableCalculator(size_t nRouters) { m_nRouters = nRouters; }

protected:
    /*! Allocate the space needed for the adj. matrix. */
    void allocateAdjMatrix();

    /*! ??? This is also to incorporate zero cost links */
    void initMatrix();

    /*!Constructs an adj. matrix to calculate with. pMap The map to populate with the adj. data. */
    void makeAdjMatrix(const std::vector<NlsrAdjLsa *> adjLsaList, Map& pMap);

    /*! Returns how many links a router in the matrix has.sRouter The router to count the links of. */
    int getNumOfLinkfromAdjMatrix(int sRouter);

    void freeAdjMatrix();

    /*!Adjust a link cost in the adj. matrix. */
    void adjustAdMatrix(int source, int link, double linkCost);

    /*! Populates temp. variables with the link costs for some router. */
    void getLinksFromAdjMatrix(int* links, double* linkCosts, int source);

    /*! Allocates an array large enough to hold multipath calculation temps. */
    void allocateLinks();

    void allocateLinkCosts();

    void freeLinks();

    void freeLinksCosts();

    void setNoLink(int nl)
    {
        vNoLink = nl;
    }
};

class LinkStateRoutingTableCalculator: public RoutingTableCalculator
{
private:
    int* m_parent;
    double* m_distance;
    bool m_isDryRun;
    iName m_thisRouterName;
    Router* router = nullptr;

    static const int EMPTY_PARENT;
    static const double INF_DISTANCE;
    static const int NO_MAPPING_NUM;

    static const double MATH_PI;
    static const double UNKNOWN_DISTANCE;

public:
    static const int NO_NEXT_HOP;

public:
    LinkStateRoutingTableCalculator(size_t nRouters, Router *routers)
        : RoutingTableCalculator(nRouters)
    {
        router = routers;
        }

    void calculatePath(Map& pMap, RoutingTable& rt, const std::vector<NlsrAdjLsa *>& adjLsaList);

private:
     /*! Performs a Dijkstra's calculation over the adjacency matrix. */
    void doDijkstraPathCalculation(int sourceRouter);

    /*! Sort the elements of a list. The cost between two nodes can be zero or greater than zero. */
    void sortQueueByDistance(int* Q, double* dist, int start, int element);

    /*! Returns whether an element has been visited yet.  */
    int isNotExplored(int* Q, int u, int start, int element);
    void addAllLsNextHopsToRoutingTable(AdjacencyList* adjacencies, RoutingTable& rt, Map& pMap, uint32_t sourceRouter);

    /*! Determines a destination's next hop.  */
    int getLsNextHop(int dest, int source);
    void allocateParent();
    void allocateDistance();
    void freeParent();
    void freeDistance();
};

//class AdjacencyList;
//class Router;
//
//class HyperbolicRoutingCalculator
//{
//public:
//  HyperbolicRoutingCalculator(size_t nRouters, bool isDryRun, iName thisRouterName)
//    : m_nRouters(nRouters)
//    , m_isDryRun(isDryRun)
//    , m_thisRouterName(thisRouterName)
//  {
//  }
//
//  void calculatePath(Map& map, RoutingTable& rt, Router& lsdb, AdjacencyList& adjacencies);
//
//private:
//  double getHyperbolicDistance(Router& lsdb, iName src, iName dest);
//  void addNextHop(iName destinationRouter, int ifIndex, double cost, RoutingTable& rt);
//  double calculateHyperbolicDistance(double rI, double rJ, double deltaTheta);
//  double calculateAngularDistance(std::vector<double> angleVectorI, std::vector<double> angleVectorJ);
//
//private:
//  const size_t m_nRouters;
//  const bool m_isDryRun;
//  const iName m_thisRouterName;
//
//  static const double MATH_PI;
//  static const double UNKNOWN_DISTANCE;
//  static const double UNKNOWN_RADIUS;
//};

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_ROUTINGTABLECALCULATOR_H_ */
