/*
 * state.cc
 *
 *  Created on: Sep 3, 2020
 *      Author: root
 */
#include "inet/routing/nlsr/PSync/detail/state.h"

namespace inet {
namespace nlsr {

State::State()
{
}

State::~State()
{
}

void State::addContent(iName& prefix)
{
  m_content.push_back(prefix);
}

std::ostream& operator<<(std::ostream& os, const State& state)  // TODO
{
  auto content = state.getContent();

  os << "[";
//  std::copy(content.begin(), content.end(), make_ostream_joiner(os, ", "));
  os << "]";

  return os;
}

} // namespace nlsr
} // namespace inet



