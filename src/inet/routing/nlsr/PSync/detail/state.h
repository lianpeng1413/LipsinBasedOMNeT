/*
 * state.h
 *
 *  Created on: Sep 3, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_PSYNC_DETAIL_STATE_H_
#define INET_ROUTING_NLSR_PSYNC_DETAIL_STATE_H_

#include <iostream>
#include "inet/networklayer/contract/ndn/iName.h"

namespace inet {
namespace nlsr {

enum {
  PSyncContent = 128
};

class State
{
private:
    std::vector<iName > m_content;

public:
    State();
    ~State();

    void addContent(iName& prefix);
    const std::vector<iName> getContent() const { return m_content; }

};

std::ostream& operator<<(std::ostream& os, const State& State);

} // namespace nlsr
} // namespace inet


#endif /* INET_ROUTING_NLSR_PSYNC_DETAIL_STATE_H_ */
