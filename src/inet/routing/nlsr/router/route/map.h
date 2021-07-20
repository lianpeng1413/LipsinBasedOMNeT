/*
 * map.h
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_ROUTE_MAP_H_
#define INET_ROUTING_NLSR_ROUTER_ROUTE_MAP_H_

#include <map>
#include <memory>
#include <iostream>
#include <vector>

#include "inet/routing/nlsr/neighbor/adjacencyList.h"
#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

#include "inet/routing/nlsr/router/route/fibEntry_m.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/linklayer/common/MacAddress_m.h"
#include "inet/routing/nlsr/router/route/nextHopList.h"
#include "inet/networklayer/contract/ndn/iType.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/optional.h"

#include <boost/multi_index/identity_fwd.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/tag.hpp>

namespace inet{
namespace nlsr {

struct MapEntry {
  iName router;
  int32_t mappingNumber = -1;

  MapEntry(const iName& rtrName, int32_t mn):router(rtrName),mappingNumber(mn){}
};

namespace detail {

using namespace boost::multi_index;

  // Define tags so that we can search by different indices.
struct byRouterName {};
struct byMappingNumber{};
using entryContainer = multi_index_container<
  MapEntry,
  indexed_by<
    hashed_unique<tag<byRouterName>,
                  member<MapEntry, iName, &MapEntry::router>,
                  std::hash<iName>>,
    hashed_unique<tag<byMappingNumber>,
                  member<MapEntry, int32_t, &MapEntry::mappingNumber>>
    >
  >;

} // namespace detail

class Map
{
public:
  Map(): m_mappingIndex(0) { }
  ~Map(){}

  /*! Add a map entry to this map. Adds a router to this map. Each entry is also given an arbitrary,
    ascending mappingNo (mapping number).  */
  void addEntry(const iName& rtrName);

  /*! Populates the Map with AdjacencyLsas.
    IteratorType must an iterator type, and begin to end must represent a valid range. */
  template<typename IteratorType>
  void createFromAdjLsdb(IteratorType begin, IteratorType end)
  {
      for (auto lsa = begin; lsa != end; lsa++) {
          addEntry((*lsa)->getHeader().getOriginRouter());
          for (const auto& Neighbor : (*lsa)->getM_adl()->getAdjList()) {
              addEntry(Neighbor->getNeighborName());
          }
      }
  }

  /*! Populates the Map with CoordinateLsas.
    IteratorType must an iterator type, and begin to end must represent a valid range. */
  template<typename IteratorType>
  void createFromCoordinateLsdb(IteratorType begin, IteratorType end)
  {
      BOOST_STATIC_ASSERT_MSG(is_iterator<IteratorType>::value, "IteratorType must be an iterator!");
      for (auto lsa = begin; lsa != end; lsa++) {
          addEntry(lsa->getOriginRouter());
      }
  }

  nonstd::optional<iName> getRouterNameByMappingNo(int32_t mn) const;

  nonstd::optional<int32_t> getMappingNoByRouterName(const iName& rName);
  size_t getMapSize() const { return m_entries.size(); }

private:
  bool addEntry(MapEntry& mpe);

  int32_t m_mappingIndex;
  inet::nlsr::detail::entryContainer m_entries;
};

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_ROUTER_ROUTE_MAP_H_ */
