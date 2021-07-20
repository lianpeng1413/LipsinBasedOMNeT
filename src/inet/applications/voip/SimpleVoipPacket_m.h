//
// Generated file, do not edit! Created by nedtool 5.6 from inet/applications/voip/SimpleVoipPacket.msg.
//

#ifndef __INET_SIMPLEVOIPPACKET_M_H
#define __INET_SIMPLEVOIPPACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class SimpleVoipPacket;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/applications/voip/SimpleVoipPacket.msg:28</tt> by nedtool.
 * <pre>
 * //
 * // Represents a voice packet used by SimpleVoipSender / SimpleVoipReceiver 
 * //
 * class SimpleVoipPacket extends FieldsChunk
 * {
 *     uint16_t totalLengthField;         // length of total SimpleVoipPacket in bytes
 *     unsigned int talkspurtID;          // identifies the talkspurt
 *     unsigned int talkspurtNumPackets;  // number of all packets of current talkspurt
 *     unsigned int packetID;             // 0..talkspurtNumPackets-1
 *     simtime_t voipTimestamp;            // "mouth" timestamp of begin of voice in this packet
 *     simtime_t voiceDuration;            // duration of voice in this packet
 * }
 * </pre>
 */
class INET_API SimpleVoipPacket : public ::inet::FieldsChunk
{
  protected:
    uint16_t totalLengthField = 0;
    unsigned int talkspurtID = 0;
    unsigned int talkspurtNumPackets = 0;
    unsigned int packetID = 0;
    omnetpp::simtime_t voipTimestamp = SIMTIME_ZERO;
    omnetpp::simtime_t voiceDuration = SIMTIME_ZERO;

  private:
    void copy(const SimpleVoipPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SimpleVoipPacket&);

  public:
    SimpleVoipPacket();
    SimpleVoipPacket(const SimpleVoipPacket& other);
    virtual ~SimpleVoipPacket();
    SimpleVoipPacket& operator=(const SimpleVoipPacket& other);
    virtual SimpleVoipPacket *dup() const override {return new SimpleVoipPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual uint16_t getTotalLengthField() const;
    virtual void setTotalLengthField(uint16_t totalLengthField);
    virtual unsigned int getTalkspurtID() const;
    virtual void setTalkspurtID(unsigned int talkspurtID);
    virtual unsigned int getTalkspurtNumPackets() const;
    virtual void setTalkspurtNumPackets(unsigned int talkspurtNumPackets);
    virtual unsigned int getPacketID() const;
    virtual void setPacketID(unsigned int packetID);
    virtual omnetpp::simtime_t getVoipTimestamp() const;
    virtual void setVoipTimestamp(omnetpp::simtime_t voipTimestamp);
    virtual omnetpp::simtime_t getVoiceDuration() const;
    virtual void setVoiceDuration(omnetpp::simtime_t voiceDuration);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SimpleVoipPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SimpleVoipPacket& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_SIMPLEVOIPPACKET_M_H

