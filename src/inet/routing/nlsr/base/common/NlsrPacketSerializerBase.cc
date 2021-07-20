/*
 * NlsrPacketSerializer.cc
 *
 *  Created on: Aug 17, 2020
 *      Author: root
 */

#include "../common/NlsrPacketSerializerBase.h"

#include "inet/common/packet/serializer/ChunkSerializerRegistry.h"
#include "inet/routing/nlsr/base/common/NlsrPacketBase_m.h"
#ifdef WITH_NLSR
#include "inet/routing/nlsr/NlsrPacketSerializer.h"
#endif // #ifdef WITH_NLSR

namespace inet {
namespace nlsr {

Register_Serializer(NlsrPacketBase, NlsrPacketSerializerBase);

void NlsrPacketSerializerBase::serialize(MemoryOutputStream& stream, const Ptr<const Chunk>& chunk) const
{
    throw cRuntimeError("NlsrPacketBase is not serializable, should use specific nlsr chunks");
}

const Ptr<Chunk> NlsrPacketSerializerBase::deserialize(MemoryInputStream& stream) const
{
    auto startPos = stream.getPosition();
    int nlsrVer = stream.readUint8();

    //TODO should register nlsr<version>Serializer classes to nlsrSerializer and deserializer choose a serializer class based on version field
    switch (nlsrVer) {
#ifdef WITH_NLSR
        case 2:
            stream.seek(startPos);
            return nlsr::NlsrPacketSerializer().deserialize(stream);
            break;
#endif // #ifdef WITH_Nlsr
        default: {
            auto nlsrPacket = makeShared<NlsrPacketBase>();
            nlsrPacket->markIncorrect();
            nlsrPacket->setVersion(nlsrVer);
            int nlsrType = stream.readUint8();
            nlsrPacket->setType(static_cast<NlsrPacketType>(nlsrType));
            uint16_t packetLength = stream.readUint16Be();
            nlsrPacket->setPacketLengthField(packetLength);
            nlsrPacket->setChunkLength(B(packetLength));
            nlsrPacket->setInterestName(stream.readNdnName());  //TODO readInterestName()
            uint16_t curLength = B(stream.getPosition() - startPos).get();
            if (packetLength > curLength)
                stream.readByteRepeatedly(0, packetLength - curLength);
            return nlsrPacket;
        }
    }
}

} // namespace nlsr
} // namespace inet



