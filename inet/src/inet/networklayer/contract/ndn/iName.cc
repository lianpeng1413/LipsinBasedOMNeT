/*
 * iName.cc
 *
 *  Created on: Aug 19, 2020
 *      Author: root
 */

#include <sstream>
#include <cstring>
#include "iName.h"

namespace inet{

/**
 * Buffer length needed to hold a NAME in string form
 */
//static const int NAME_STRING_SIZE = 40;
const iName iName::LOCAL_ADDRESS("/localhost/nlsr");
const iName iName::NLSR_ROUTERS_MCAST("NLSR/MULTICAST");

void iName::set(std::string tag0, std::string prefix1, std::string tail2)
{
    tag = tag0;
    prefix = prefix1;
    tail = tail2;

    std::string interestName;
    interestName.append("/");
    interestName.append(tag0);
    interestName.append("/");
    interestName.append(prefix1);
    interestName.append("/");
    interestName.append(tail2);

    m_name = interestName;
}

void iName::set(const char *addr)
{
    if (!addr)
        throw cRuntimeError("ndn: cannot interpret address string `%s'", addr);
}

void iName::set(const std::string text)
{
    std::string buf[3];
    if (text.size() == 0)
        throw cRuntimeError("interest name is null");

    std::string pattern = "/";
    std::vector<std::string> result(pattern_seg(text, pattern));

    for(int i=0; i<3; i++){
        buf[i] = result[i];
    }
    set(buf[0], buf[1], buf[2]);
}

std::vector<std::string> iName::pattern_seg(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> vec;
    std::string buf(str);
    buf += pattern;
    int size = buf.size();
    for(int i=0; i < size; i++)
    {
        pos = buf.find('/', i);
        if(pos < size)
        {
            std::string s = buf.substr(i, pos-i);
            vec.push_back(s);
            i = pos + pattern.size()-1;
        }
    }
    return vec;
}

std::string iName::str() const
{
    std::string interestName;
    interestName.append("/");
    interestName.append(tag);
    interestName.append("/");
    interestName.append(prefix);
    interestName.append("/");
    interestName.append(tail);
//    char buf[NAME_STRING_SIZE];
//    sprintf(buf, "/%s/%s/%s", tag.c_str(), prefix.c_str(), tail.c_str());
    return interestName;
}

bool iName::empty() const
{
    return m_name.empty();
}

bool operator<(const iName &lhs, const iName &rhs)
{
//    if(lhs.str() < rhs.str())
//        return true;
//    else
//        return false;
    return lhs.str() < rhs.str();
//    return (std::strcmp(lhs.str().c_str(), rhs.str().c_str()) ==0 ) ? 0 : 1;
}

bool operator==(const iName &lhs, const iName &rhs)
{
    return lhs.tag ==rhs.tag && lhs.prefix ==rhs.prefix && lhs.tail ==rhs.tail;
}

bool operator!=(const iName &lhs, const iName &rhs)
{
    return !(lhs == rhs);
}



}//namespace inet

//namespace std {
//
//size_t hash<inet::iName>::operator()(const inet::iName& name) const
//{
//    std::hash<std::string > hash_str;
//    std::string hashName = name.str();
//    return hash_str(hashName);
//}
//
//} // namespace std
