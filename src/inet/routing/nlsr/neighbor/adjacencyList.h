/*
 * adjacencyList.h
 *
 *  Created on: Aug 30, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_NEIGHBOR_ADJACENCYLIST_H_
#define INET_ROUTING_NLSR_NEIGHBOR_ADJACENCYLIST_H_

#include <vector>
#include <list>

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"

namespace inet{
namespace nlsr{

class Neighbor;

class INET_API AdjacencyList
{
private:
    std::list<Neighbor *> m_adjList;

public:
    AdjacencyList();
    ~AdjacencyList();
    AdjacencyList(const AdjacencyList& other);

    bool insert(Neighbor* adjacent);
    std::list<Neighbor* >& getAdjList();
    const std::list<Neighbor *>& getAdjList() const;
    bool isNeighbor(const iName& adjName) const;

    int getNumOfActiveNeighbor() const;
    Neighbor* getNeighbor(const iName& adjName);
    bool operator==(const AdjacencyList& adl) const;
    int size() const  { return m_adjList.size(); }
    void reset() { m_adjList.clear();}

    Neighbor* findNeighbor(const iName& adjName);
    void deleteNeighbor(const iName& adjName);
};

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_NEIGHBOR_ADJACENCYLIST_H_ */
