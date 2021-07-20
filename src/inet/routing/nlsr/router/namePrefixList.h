/*
 * namePrefxiList.h
 *
 *  Created on: Sep 2, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_NAMEPREFIXLIST_H_
#define INET_ROUTING_NLSR_ROUTER_NAMEPREFIXLIST_H_

#include <list>
#include <string>

#include "inet/networklayer/contract/ndn/iName.h"

namespace inet{
namespace nlsr {

class NamePrefixList
{
public:
    using NamePair = std::tuple<iName, std::vector<std::string>>;
    enum NamePairIndex {
      NAME,
      SOURCES
    };

private:
  /*! Obtain an iterator to the entry matching name.  */
  std::vector<NamePair>::iterator get(const iName& name);

  /*! Obtain an iterator to a specific source in an entry */
  std::vector<std::string>::iterator getSource(const std::string& source, std::vector<NamePair>::iterator& entry);
  std::vector<NamePair> m_names;

public:
  NamePrefixList();
  ~NamePrefixList();
  NamePrefixList(const NamePrefixList& other);

  NamePrefixList(const std::initializer_list<iName>& names);
  NamePrefixList(const std::initializer_list<NamePrefixList::NamePair>& namesAndSources);

  /*! inserts name into NamePrefixList */
  bool insert(const iName& name, const std::string& source = "");

  /*! removes name from NamePrefixList  */
  bool remove(const iName& name, const std::string& source = "");

  void sort();

  size_t size() const { return m_names.size(); }

  std::list<iName> getNames() const;

  bool operator==(const NamePrefixList& other) const;

  /*! Returns how many unique sources this name has.  */
  uint32_t countSources(const iName& name) const;

  /*! Returns the sources that this name has. */
  const std::vector<std::string> getSources(const iName& name) const;

  void clear() { m_names.clear();}
};

std::ostream& operator<<(std::ostream& os, const NamePrefixList& list);

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_ROUTER_NAMEPREFIXLIST_H_ */
