/*
 * routingTableCalculator.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#include <memory>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <boost/math/constants/constants.hpp>

#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/Simsignals.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

#include "inet/routing/nlsr/router/route/routingTableCalculator.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"
#include "inet/routing/nlsr/router/route/nextHop.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/routing/nlsr/Nlsr.h"
#include "inet/routing/nlsr/router/route/map.h"
#include "inet/routing/nlsr/router/optional.h"

namespace inet{
namespace nlsr {

const int LinkStateRoutingTableCalculator::EMPTY_PARENT = -12345; //-12345
const double LinkStateRoutingTableCalculator::INF_DISTANCE = 2147483647;
const int LinkStateRoutingTableCalculator::NO_MAPPING_NUM = -1;
const int LinkStateRoutingTableCalculator::NO_NEXT_HOP = -12345;

void RoutingTableCalculator::allocateAdjMatrix()
{
    adjMatrix = new double*[m_nRouters];

    for (size_t i = 0; i < m_nRouters; ++i) {
        adjMatrix[i] = new double[m_nRouters];
    }
}

void RoutingTableCalculator::initMatrix()
{
    for (size_t i = 0; i < m_nRouters; i++) {
        for (size_t j = 0; j < m_nRouters; j++) {
            adjMatrix[i][j] = Neighbor::NON_ADJACENT_COST;
        }
    }
}

void RoutingTableCalculator::makeAdjMatrix(const std::vector<NlsrAdjLsa *> adjLsaList, Map& pMap)
{
    // For each LSA represented in the map
    for (const auto& adjLsa : adjLsaList) {
        nonstd::optional<int32_t> row = pMap.getMappingNoByRouterName(adjLsa->getHeader().getOriginRouter());

        auto adl = adjLsa->getM_adl()->getAdjList();
        // For each adjacency represented in the LSA
        for (const auto& adjacent : adl) {
            nonstd::optional<int32_t> col = pMap.getMappingNoByRouterName(adjacent->getNeighborName());
            double cost = adjacent->getLinkCost();

            if (row && col && *row < static_cast<int32_t>(m_nRouters)
                    && *col < static_cast<int32_t>(m_nRouters))
            {
                adjMatrix[*row][*col] = cost;
                adjMatrix[*col][*row] = cost;
            }
        }
    }

    // Links that do not have the same cost for both directions should
    // have their costs corrected:
    //
    //   If the cost of one side of the link is NON_ADJACENT_COST (i.e. broken) or negative,
    //   both direction of the link should have their cost corrected to NON_ADJACENT_COST.
    //
    //   Otherwise, both sides of the link should use the larger of the two costs.
    //
    // Additionally, this means that we can halve the amount of space
    // that the matrix uses by only maintaining a triangle.
    // - But that is not yet implemented.
    for (size_t row = 0; row < m_nRouters; ++row) {
        for (size_t col = 0; col < m_nRouters; ++col) {
            double toCost = adjMatrix[row][col];
            double fromCost = adjMatrix[col][row];
            if (fromCost != toCost) {
                double correctedCost = Neighbor::NON_ADJACENT_COST;

                if (toCost >= 0 && fromCost >= 0) {
                    // If both sides of the link are up, use the larger cost else break the link
                    correctedCost = std::max(toCost, fromCost);
                }

                EV_INFO << "Cost between [" << row << "][" << col << "] and [" << col << "][" << row <<
                  "] are not the same (" << toCost << " != " << fromCost << "). " <<
                  "Correcting to cost: " << correctedCost << endl;

                adjMatrix[row][col] = correctedCost;
                adjMatrix[col][row] = correctedCost;
            }
        }
    }
}

void RoutingTableCalculator::adjustAdMatrix(int source, int link, double linkCost)
{
    for (int i = 0; i < static_cast<int>(m_nRouters); i++) {
        if (i == link) {
            adjMatrix[source][i] = linkCost;
        }
        else {
            // if "i" is not a link to the source, set it's cost to a non adjacent value.
            adjMatrix[source][i] = Neighbor::NON_ADJACENT_COST;
        }
    }
}

int RoutingTableCalculator::getNumOfLinkfromAdjMatrix(int sRouter)
{
    int noLink = 0;

    for (size_t i = 0; i < m_nRouters; i++) {
        if (adjMatrix[sRouter][i] >= 0 && i != static_cast<size_t>(sRouter)) { // make sure "i" is not self
            noLink++;
        }
    }
    return noLink;
}

void RoutingTableCalculator::getLinksFromAdjMatrix(int* links, double* linkCosts, int source)
{
    int j = 0;

    for (size_t i = 0; i < m_nRouters; i++) {
        if (adjMatrix[source][i] >= 0 && i != static_cast<size_t>(source)) {// make sure "i" is not self
            links[j] = i;
            linkCosts[j] = adjMatrix[source][i];
            j++;
        }
    }
}

void RoutingTableCalculator::freeAdjMatrix()
{
    for (size_t i = 0; i < m_nRouters; ++i) {
        delete [] adjMatrix[i];
    }
    delete [] adjMatrix;
}

void RoutingTableCalculator::allocateLinks()
{
    links = new int[vNoLink];
}

void RoutingTableCalculator::allocateLinkCosts()
{
    linkCosts = new double[vNoLink];
}

void RoutingTableCalculator::freeLinks()
{
    delete [] links;
}
void RoutingTableCalculator::freeLinksCosts()
{
    delete [] linkCosts;
}

//TODO Modify this function.
void LinkStateRoutingTableCalculator::calculatePath(Map& pMap, RoutingTable& rt, const std::vector<NlsrAdjLsa *>& adjLsaList)
{
    EV_INFO << "LinkStateRoutingTableCalculator::calculatePath Called. \n";
    allocateAdjMatrix();
    initMatrix();
    makeAdjMatrix(adjLsaList, pMap);

    nonstd::optional<int32_t> sourceRouter = pMap.getMappingNoByRouterName(router->getRouterID());
    allocateParent(); // These two matrices are used in Dijkstra's algorithm.
    allocateDistance();
    // We only bother to do the calculation if we have a router by that name.
    if (sourceRouter && router->getMaxFacesPerPrefix(router->getRouterID()) == 1) {
        // In the single path case we can simply run Dijkstra's algorithm.
        doDijkstraPathCalculation(*sourceRouter);
        // Inform the routing table of the new next hops.
        addAllLsNextHopsToRoutingTable(router->getAdjacencyList(), rt, pMap, *sourceRouter);
    }
    else {
        // Multi Path
        setNoLink(getNumOfLinkfromAdjMatrix(*sourceRouter));
        allocateLinks();
        allocateLinkCosts();
        // Gets a sparse listing of adjacencies for path calculation
        getLinksFromAdjMatrix(links, linkCosts, *sourceRouter);

        for (int i = 0 ; i < vNoLink; i++) {
            // Simulate that only the current neighbor is accessible
            adjustAdMatrix(*sourceRouter, links[i], linkCosts[i]);

            // Do Dijkstra's algorithm using the current neighbor as your start.
            doDijkstraPathCalculation(*sourceRouter);
            // Update the routing table with the calculations.
            addAllLsNextHopsToRoutingTable(router->getAdjacencyList(), rt, pMap, *sourceRouter);
        }
        freeLinks();
        freeLinksCosts();
    }
    freeParent();
    freeDistance();
    freeAdjMatrix();
}

void LinkStateRoutingTableCalculator::doDijkstraPathCalculation(int sourceRouter)
{
    int i;
    int v, u;
    int* Q = new int[m_nRouters]; // Each cell represents the router with that mapping no.
    int head = 0;
    // Initiate the parent
    for (i = 0 ; i < static_cast<int>(m_nRouters); i++) {
        m_parent[i] = EMPTY_PARENT;
        // Array where the ith element is the distance to the router with mapping no i.
        m_distance[i] = INF_DISTANCE;
        Q[i] = i;
    }
    if (sourceRouter != NO_MAPPING_NUM) {
        // Distance to source from source is always 0.
        m_distance[sourceRouter] = 0;
        sortQueueByDistance(Q, m_distance, head, m_nRouters);
        // While we haven't visited every node.
        while (head < static_cast<int>(m_nRouters)) {
            u = Q[head]; // Set u to be the current node pointed to by head.
            if (m_distance[u] == INF_DISTANCE) {
                break; // This can only happen when there are no accessible nodes.
            }
            // Iterate over the adjacent nodes to u.
            for (v = 0 ; v < static_cast<int>(m_nRouters); v++) {
                // If the current node is accessible.
                if (adjMatrix[u][v] >= 0) {
                    // And we haven't visited it yet.
                    if (isNotExplored(Q, v, head + 1, m_nRouters)) {
                        // And if the distance to this node + from this node to v
                        // is less than the distance from our source node to v
                        // that we got when we built the adj LSAs
                        if (m_distance[u] + adjMatrix[u][v] <  m_distance[v]) {
                            // Set the new distance
                            m_distance[v] = m_distance[u] + adjMatrix[u][v] ;
                            // Set how we get there.
                            m_parent[v] = u;
                        }
                    }
                }
            }
            // Increment the head position, resort the list by distance from where we are.
            head++;
            sortQueueByDistance(Q, m_distance, head, m_nRouters);
        }
    }
    delete [] Q;
}

void LinkStateRoutingTableCalculator::addAllLsNextHopsToRoutingTable(AdjacencyList* adjacencies,
                                                                RoutingTable& rt, Map& pMap,
                                                                uint32_t sourceRouter)
{
    EV_INFO << "LinkStateRoutingTableCalculator::addAllNextHopsToRoutingTable. \n";

    int nextHopRouter = 0;

    // For each router we have
    for (size_t i = 0; i < m_nRouters ; i++) {
        if (i != sourceRouter) {

            // Obtain the next hop that was determined by the algorithm
            nextHopRouter = getLsNextHop(i, sourceRouter);
            // If this router is accessible at all
            if (nextHopRouter != NO_NEXT_HOP) {

                // Fetch its distance
                double routeCost = m_distance[i];
                // Fetch its actual name
                nonstd::optional<iName> nextHopRouterName= pMap.getRouterNameByMappingNo(nextHopRouter);
                if (nextHopRouterName) {
                    if(adjacencies->getNeighbor(*nextHopRouterName) != nullptr){
                        NlsrInterface* neighborIf = adjacencies->getNeighbor(*nextHopRouterName)->getInterface();
                        MacAddress  nextHopMac = neighborIf->getNeighborMac();
                        int nextHopIfindex = neighborIf->getIfIndex();
                        // Add next hop to routing table
                        NextHop nh(*nextHopRouterName, nextHopIfindex, nextHopMac, routeCost);
                        rt.addNextHop(*(pMap.getRouterNameByMappingNo(i)), nh);
                    }
                }
            }
        }
    }
}

int LinkStateRoutingTableCalculator::getLsNextHop(int dest, int source)
{
    int nextHop = NO_NEXT_HOP;
    while (m_parent[dest] != EMPTY_PARENT) {
        nextHop = dest;
        dest = m_parent[dest];
    }
    if (dest != source) {
        nextHop = NO_NEXT_HOP;
    }
    return nextHop;
}

void LinkStateRoutingTableCalculator::sortQueueByDistance(int* Q, double* dist, int start, int element)
{
    for (int i = start ; i < element ; i++) {
        for (int j = i + 1; j < element; j++) {
            if (dist[Q[j]] < dist[Q[i]]) {
                int tempU = Q[j];
                Q[j] = Q[i];
                Q[i] = tempU;
            }
        }
    }
}

int LinkStateRoutingTableCalculator::isNotExplored(int* Q, int u, int start, int element)
{
    int ret = 0;
    for (int i = start; i < element; i++) {
        if (Q[i] == u) {
            ret = 1;
            break;
        }
    }
    return ret;
}

void LinkStateRoutingTableCalculator::allocateParent()
{
    m_parent = new int[m_nRouters];
}

void LinkStateRoutingTableCalculator::allocateDistance()
{
    m_distance = new double[m_nRouters];
}

void LinkStateRoutingTableCalculator::freeParent()
{
    delete [] m_parent;
}

void LinkStateRoutingTableCalculator::freeDistance()
{
    delete [] m_distance;
}

} // namespace nlsr
} // namespace inet


