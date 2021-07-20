/*
 * NlsrPacketSerializer.h
 *
 *  Created on: Aug 17, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_BASE_PACKETS_NLSRPACKETSERIALIZERBASE_H_
#define INET_ROUTING_NLSR_BASE_PACKETS_NLSRPACKETSERIALIZERBASE_H_

#include "inet/common/packet/serializer/FieldsChunkSerializer.h"

namespace inet {
namespace nlsr {

/**
 * Converts between nlsrPacket and binary (network byte order) nlsr data.
 */
class INET_API NlsrPacketSerializerBase : public FieldsChunkSerializer
{
  protected:
    virtual void serialize(MemoryOutputStream& stream, const Ptr<const Chunk>& chunk) const override;
    virtual const Ptr<Chunk> deserialize(MemoryInputStream& stream) const override;

  public:
    NlsrPacketSerializerBase() : FieldsChunkSerializer() {}
};

} // namespace nlsr
} // namespace inet


#endif /* INET_ROUTING_NLSR_BASE_PACKETS_NLSRPACKETSERIALIZERBASE_H_ */
