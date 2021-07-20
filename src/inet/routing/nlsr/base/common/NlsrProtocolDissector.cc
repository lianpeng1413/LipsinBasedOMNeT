/*
 * NlsrProtocolDissector.cc
 *
 *  Created on: Aug 17, 2020
 *      Author: root
 */

#include "../common/NlsrProtocolDissector.h"

#include "inet/common/packet/dissector/ProtocolDissectorRegistry.h"
#include "inet/routing/nlsr/base/common/NlsrPacketBase_m.h"

namespace inet {
namespace nlsr {

Register_Protocol_Dissector(&Protocol::nlsr, NlsrProtocolDissector);

void NlsrProtocolDissector::dissect(Packet *packet, const Protocol *protocol, ICallback& callback) const
{
    auto header = packet->popAtFront<NlsrPacketBase>();
    callback.startProtocolDataUnit(&Protocol::nlsr);
    callback.visitChunk(header, &Protocol::nlsr);
    callback.endProtocolDataUnit(&Protocol::nlsr);
}

} // namespace nlsr
} // namespace inet


