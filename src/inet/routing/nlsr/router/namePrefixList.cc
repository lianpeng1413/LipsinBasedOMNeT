/*
 * namePrefixList.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#include <algorithm>
#include <string>

#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/neighbor/adjacencyList.h"
#include "inet/routing/nlsr/router/namePrefixList.h"

namespace inet{
namespace nlsr {

NamePrefixList::NamePrefixList(){ }

NamePrefixList::~NamePrefixList()
{
    clear();
}

NamePrefixList::NamePrefixList(const NamePrefixList& other)
{
    this->m_names = other.m_names;
}

NamePrefixList::NamePrefixList(const std::initializer_list<iName>& names)
{
  std::vector<NamePrefixList::NamePair> namePairs;
  std::transform(names.begin(), names.end(), std::back_inserter(namePairs),
    [] (const iName& name) {
      return NamePrefixList::NamePair{name, {""}};
    });
  m_names = std::move(namePairs);
}

NamePrefixList::NamePrefixList(const std::initializer_list<NamePrefixList::NamePair>& namesAndSources)
  : m_names(namesAndSources)
{
}

std::vector<NamePrefixList::NamePair>::iterator NamePrefixList::get(const iName& name)
{
  return std::find_if(m_names.begin(), m_names.end(),
                      [&] (const NamePrefixList::NamePair& pair) {
                        return name == std::get<NamePrefixList::NamePairIndex::NAME>(pair);
                      });
}

std::vector<std::string>::iterator NamePrefixList::getSource(const std::string& source, std::vector<NamePair>::iterator& entry)
{
  return std::find_if(std::get<NamePairIndex::SOURCES>(*entry).begin(),
                      std::get<NamePairIndex::SOURCES>(*entry).end(),
                      [&] (const std::string& containerSource) {
                        return source == containerSource;
                      });
}

bool NamePrefixList::insert(const iName& name, const std::string& source)
{
  auto pairItr = get(name);
  if (pairItr == m_names.end()) {
    std::vector<std::string> sources{source};
    m_names.push_back(std::tie(name, sources));
    EV_INFO << "name: " << name.str() << " from " << source << " register success in NamPrefixList." << endl;
    return true;
  }
  else {
    std::vector<std::string>& sources = std::get<NamePrefixList::NamePairIndex::SOURCES>(*pairItr);
    auto sourceItr = getSource(source, pairItr);
    if (sourceItr == sources.end()) {
      sources.push_back(source);
      EV_INFO << "name from " << source << " register success in NamPrefixList." << endl;
      return true;
    }
  }
  return false;
}

bool NamePrefixList::remove(const iName& name, const std::string& source)
{
  auto pairItr = get(name);
  if (pairItr != m_names.end()) {
    std::vector<std::string>& sources = std::get<NamePrefixList::NamePairIndex::SOURCES>(*pairItr);
    auto sourceItr = getSource(source, pairItr);
    if (sourceItr != sources.end()) {
      sources.erase(sourceItr);
      if (sources.size() == 0) {
        m_names.erase(pairItr);
      }
      return true;
    }
  }
  return false;
}

bool NamePrefixList::operator==(const NamePrefixList& other) const
{
  return m_names == other.m_names;
}

void NamePrefixList::sort()
{
  std::sort(m_names.begin(), m_names.end());
}

std::list<iName> NamePrefixList::getNames() const
{
  std::list<iName> names;
  for (const auto& namePair : m_names) {
    names.push_back(std::get<NamePrefixList::NamePairIndex::NAME>(namePair));
  }
  return names;
}

uint32_t NamePrefixList::countSources(const iName& name) const
{
  return getSources(name).size();
}

const std::vector<std::string> NamePrefixList::getSources(const iName& name) const
{
  auto it = std::find_if(m_names.begin(), m_names.end(),
                         [&] (const NamePrefixList::NamePair& pair) {
                           return name == std::get<NamePrefixList::NamePairIndex::NAME>(pair);
                         });
  if (it != m_names.end()) {
    return std::get<NamePrefixList::NamePairIndex::SOURCES>(*it);
  }
  else {
    return std::vector<std::string>{};
  }
}

std::ostream& operator<<(std::ostream& os, const NamePrefixList& list) {
  os << "Name prefix list: {\n";
  for (const auto& name : list.getNames()) {
    os << name << "\n"
       << "Sources:\n";
    for (const auto& source : list.getSources(name)) {
      os << "  " << source << "\n";
    }
  }
  os << "}" << std::endl;
  return os;
}

} // namespace nlsr
} // namespace inet




