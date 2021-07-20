/*
 * NlsrProtocolDissector.h
 *
 *  Created on: Aug 17, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_BASE_COMMON_NLSRPROTOCOLDISSECTOR_H_
#define INET_ROUTING_NLSR_BASE_COMMON_NLSRPROTOCOLDISSECTOR_H_

#include "inet/common/INETDefs.h"
#include "inet/common/packet/dissector/ProtocolDissector.h"

namespace inet{
namespace nlsr{

class INET_API NlsrProtocolDissector : public ProtocolDissector
{
  public:
    virtual void dissect(Packet *packet, const Protocol *protocol, ICallback& callback) const override;
};
}
}



#endif /* INET_ROUTING_NLSR_BASE_COMMON_NLSRPROTOCOLDISSECTOR_H_ */
