//
// Generated file, do not edit! Created by nedtool 5.6 from inet/linklayer/ppp/PppFrame.msg.
//

#ifndef __INET_PPPFRAME_M_H
#define __INET_PPPFRAME_M_H

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

class PppHeader;
class PppTrailer;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

// cplusplus {{
const B PPP_HEADER_LENGTH = B(5);
const B PPP_TRAILER_LENGTH = B(2);
// }}

/**
 * Class generated from <tt>inet/linklayer/ppp/PppFrame.msg:44</tt> by nedtool.
 * <pre>
 * //
 * // PPP frame.
 * //
 * // Constant-value header fields are not modelled:
 * // Flag (=0x7e), address (=0xff), control (=0x03), CRC (bitError())
 * //
 * // CRC is modelled only via cMessage's bit error attribute.
 * class PppHeader extends FieldsChunk
 * {
 *     chunkLength = PPP_HEADER_LENGTH;
 *     short flag = 0x7e;      //1 byte
 *     short address = 0xff;   //1 byte
 *     short control = 0x03;   //1 byte
 *     int protocol = -1;      //2 byte
 * }
 * </pre>
 */
class INET_API PppHeader : public ::inet::FieldsChunk
{
  protected:
    short flag = 0x7e;
    short address = 0xff;
    short control = 0x03;
    int protocol = -1;

  private:
    void copy(const PppHeader& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PppHeader&);

  public:
    PppHeader();
    PppHeader(const PppHeader& other);
    virtual ~PppHeader();
    PppHeader& operator=(const PppHeader& other);
    virtual PppHeader *dup() const override {return new PppHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual short getFlag() const;
    virtual void setFlag(short flag);
    virtual short getAddress() const;
    virtual void setAddress(short address);
    virtual short getControl() const;
    virtual void setControl(short control);
    virtual int getProtocol() const;
    virtual void setProtocol(int protocol);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PppHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PppHeader& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ppp/PppFrame.msg:53</tt> by nedtool.
 * <pre>
 * class PppTrailer extends FieldsChunk
 * {
 *     chunkLength = PPP_TRAILER_LENGTH; //FIXME correct value is 3, but old inet was used 2 bytes
 *     short fcs = 0;      // frame check sequence, 2 byte
 *     short flag = 0x7e;  // 1 byte, omitted for successive PPP packets
 * }
 * </pre>
 */
class INET_API PppTrailer : public ::inet::FieldsChunk
{
  protected:
    short fcs = 0;
    short flag = 0x7e;

  private:
    void copy(const PppTrailer& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PppTrailer&);

  public:
    PppTrailer();
    PppTrailer(const PppTrailer& other);
    virtual ~PppTrailer();
    PppTrailer& operator=(const PppTrailer& other);
    virtual PppTrailer *dup() const override {return new PppTrailer(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual short getFcs() const;
    virtual void setFcs(short fcs);
    virtual short getFlag() const;
    virtual void setFlag(short flag);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PppTrailer& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PppTrailer& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_PPPFRAME_M_H

