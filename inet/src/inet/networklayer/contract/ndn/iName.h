/*
 * iName.h
 *
 *  Created on: Aug 19, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_CONTRACT_NDN_INAME_H_
#define INET_NETWORKLAYER_CONTRACT_NDN_INAME_H_

#include <iostream>
#include <string>
#include <iterator>
#include <string.h>
#include <array>

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/ndn/iName.h"
//#include "inet/common/bloomfilter/hash/MurmurHash3.h"

namespace inet {

class InterfaceToken;

/**
 * Stores a named data networking Interest Name in an efficient way.
 */
class iName
{
  private:
    std::string tag;
    std::string prefix;
    std::string tail;

  public:
    static const iName LOCAL_ADDRESS;
    static const iName NLSR_ROUTERS_MCAST;
    std::string m_name;

    /* Default constructor, initializes to null. */
    iName() { tag = ""; prefix = ""; tail = "";}

    /* interest name format: "/tag/prefix/tail" */
    iName(std::string tag0, std::string prefix1, std::string tail2) { set(tag0, prefix1, tail2); }

    /* interest name given as text: "/name/prefix1/tail2" */
    explicit iName(const std::string text) { set(text); }

    /* Copy constructor */
    iName(const iName& obj): tag(obj.getTag()), prefix(obj.getPrefix()), tail(obj.getTail()) { }

    ~iName() {}

    /* interest name format: "/tag/prefix/tail" */
    void set(std::string tag0, std::string prefix1, std::string tail2);

    /* interest name given as text: "/tag/prefix/tail"  */
    void set(const std::string t);
    void set(const char *addr);
    explicit iName(const char *addr) { set(addr); }

    std::vector<std::string> pattern_seg(std::string str, std::string pattern);

    /* Assignment */
    iName& operator=(const iName& obj) { tag = obj.tag; prefix = obj.prefix; tail = obj.tail; return *this; }

    /* Returns true if the two name are equal */
    bool equals(const iName& toCmp) const {
        return tag ==toCmp.tag && prefix ==toCmp.prefix && tail ==toCmp.tail;
    }

    friend bool operator<(const iName &lhs, const iName &rhs);
    friend bool operator==(const iName &lhs, const iName &rhs);/* Returns equals(name). */
    friend bool operator!=(const iName &lhs, const iName &rhs);/* Returns !equals(addr). */

    /* Returns the string representation of the name. */
    std::string str() const;
    bool empty() const;

    const std::string getTag() const { return tag; }
    const std::string getPrefix() const { return prefix; }
    const std::string getTail() const { return tail; }
    const std::string getInterestName() const { return m_name;}
};

    inline std::ostream& operator<<(std::ostream& os, const iName& name)
    {
        return os << name.str();
    }

} // namespace inet

//namespace std {

//template<>
//struct hash<inet::iName>
//{
//  size_t operator()(const inet::iName& name) const;
//};

//} // namespace std

#endif /* INET_NETWORKLAYER_CONTRACT_NDN_INAME_H_ */
