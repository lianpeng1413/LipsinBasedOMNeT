/*
 * map.cc
 *
 *  Created on: Sep 1, 2020
 *      Author: root
 */
#include <map>
#include <memory>
#include <iostream>
#include <vector>

#include "inet/common/INETDefs.h"
#include "map.h"
#include "inet/routing/nlsr/Nlsr.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet {
namespace nlsr {

void Map::addEntry(const iName& rtrName)
{
    MapEntry me {rtrName, m_mappingIndex};

    if (addEntry(me)) {
        EV_INFO << "router:" << me.router.str() << ", m_mappingIndex:" << m_mappingIndex << endl;
        m_mappingIndex++;
  }
}

bool Map::addEntry(MapEntry& mpe)
{
    return m_entries.insert(mpe).second;
}

nonstd::optional<iName> Map::getRouterNameByMappingNo(int32_t mn) const
{
    auto&& mappingNumberView = m_entries.get<detail::byMappingNumber>();
    auto it = mappingNumberView.find(mn);
    return it == mappingNumberView.end() ? nonstd::nullopt : nonstd::optional<iName> (it->router);
}

nonstd::optional<int32_t> Map::getMappingNoByRouterName(const iName& rName)
{
    auto&& routerNameView = m_entries.get<detail::byRouterName>();
    auto it = routerNameView.find(rName);
    return it == routerNameView.end() ? nonstd::nullopt : nonstd::optional<int32_t> (it->mappingNumber);
}

} // namespace nlsr
} // namespace inet


