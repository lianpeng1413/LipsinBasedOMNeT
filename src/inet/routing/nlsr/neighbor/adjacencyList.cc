/*
 * adjacencyList.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#include <algorithm>
#include <list>

#include "inet/routing/nlsr/neighbor/adjacencyList.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"

namespace inet{
namespace nlsr {

AdjacencyList::AdjacencyList(){}

AdjacencyList::~AdjacencyList()
{
    reset();
}

AdjacencyList::AdjacencyList(const AdjacencyList& other)
{
    m_adjList = other.m_adjList;
}

/** If the neighbor is already on the list then it is replaced, else
 * a neighbor is added to the end of the list. */
bool AdjacencyList::insert(Neighbor* adjacent)
{
    deleteNeighbor(adjacent->getNeighborName());
    m_adjList.push_back(adjacent);

    EV_INFO << "Neighbor (" << adjacent->getNeighborName().str() << ") is added." << endl;
    return true;
}

std::list<Neighbor *>& AdjacencyList::getAdjList()
{
    return m_adjList;
}

const std::list<Neighbor *>& AdjacencyList::getAdjList() const
{
    return m_adjList;
}

Neighbor* AdjacencyList::getNeighbor(const iName& adjName)
{
    auto it = m_adjList.begin();
    for ( ; it!= m_adjList.end(); it++){
        if((*it)->getNeighborName() == adjName){
            break;
        }
    }
    if (it != m_adjList.end()) {
        return (*it);
    }
    else
        return nullptr;
}

bool AdjacencyList::operator==(const AdjacencyList& adl) const
{
  auto theirList = adl.getAdjList();
  if (m_adjList.size() != theirList.size()) {
    return false;
  }

  std::set<Neighbor *> ourSet(m_adjList.cbegin(), m_adjList.cend());
  std::set<Neighbor *> theirSet(theirList.cbegin(), theirList.cend());

  return ourSet == theirSet;
}

bool AdjacencyList::isNeighbor(const iName& adjName) const
{
    auto it = m_adjList.begin();
    for ( ; it!= m_adjList.end(); it++){
        if((*it)->getNeighborName() == adjName){
            break;
        }
    }
    if (it != m_adjList.end()) {
        return true;
    }
    else
        return false;
}

int32_t AdjacencyList::getNumOfActiveNeighbor() const
{
    int32_t actNbrCount = 0;
    for (const auto& adjacent: m_adjList) {
        if (adjacent->getState() != Neighbor::DOWN_STATE ) {
            actNbrCount++;
        }
    }
    return actNbrCount;
}

Neighbor* AdjacencyList::findNeighbor(const iName& adjName)
{
    auto it = m_adjList.begin();
    for ( ; it!= m_adjList.end(); it++){
        if((*it)->getNeighborName() == adjName){
            break;
        }
    }
    if (it != m_adjList.end()) {
        return (*it);
    }
    else
        return nullptr;
}

void AdjacencyList::deleteNeighbor(const iName& adjName)
{ // Find neighbor and delete it.
    EV_INFO << "delete neighbor: " << adjName.str()<< endl;
    auto it = m_adjList.begin();
    while (it != m_adjList.end()) {
        if ((*it)->getNeighborName() == adjName)
        {
            delete (*it);//release memory
            it = m_adjList.erase(it); //delete it pointer
        }
        else {
            it++;
        }
    }
}

} // namespace nlsr
} // namespace inet
