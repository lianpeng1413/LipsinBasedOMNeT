//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/contract/ndn/Interest.msg.
//

#ifndef __INET_INTEREST_M_H
#define __INET_INTEREST_M_H

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

class Interest;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/ProtocolTag_m.h" // import inet.common.ProtocolTag

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress

#include "inet/networklayer/contract/ndn/ndnFields_m.h" // import inet.networklayer.contract.ndn.ndnFields


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/contract/ndn/Interest.msg:25</tt> by nedtool.
 * <pre>
 * class Interest extends FieldsChunk
 * {
 *     chunkLength = B(128);
 * 
 *     iName interestName;
 *     iName source;
 * 
 *     unsigned char type = 0;
 *     int hotCount = 0;
 *     short prefixLength = 1;
 *     bool flood = false;
 *     bool canBePrefix = false;
 *     bool MustBeFresh = false;
 *     simtime_t InterestLifeTime;		// default omitted
 *     unsigned int hopLimit = 256;
 * 
 *     Port_t portNumber1 = 0;
 *     Port_t portNumber2 = 0;
 *     uint16_t MTU = 0;
 *     uint16_t checksum = 0;
 *     long Nonce;
 *     //  	paths trace;
 *     MacAddress MAC;   //48bits  
 *     uint16_t totalLength = 0;
 * 
 * }
 * </pre>
 */
class INET_API Interest : public ::inet::FieldsChunk
{
  protected:
    iName interestName;
    iName source;
    unsigned char type = 0;
    int hotCount = 0;
    short prefixLength = 1;
    bool flood = false;
    bool canBePrefix = false;
    bool MustBeFresh = false;
    omnetpp::simtime_t InterestLifeTime = SIMTIME_ZERO;
    unsigned int hopLimit = 256;
    Port_t portNumber1 = 0;
    Port_t portNumber2 = 0;
    uint16_t MTU = 0;
    uint16_t checksum = 0;
    long Nonce = 0;
    MacAddress MAC;
    uint16_t totalLength = 0;

  private:
    void copy(const Interest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Interest&);

  public:
    Interest();
    Interest(const Interest& other);
    virtual ~Interest();
    Interest& operator=(const Interest& other);
    virtual Interest *dup() const override {return new Interest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const iName& getInterestName() const;
    virtual iName& getInterestNameForUpdate() { handleChange();return const_cast<iName&>(const_cast<Interest*>(this)->getInterestName());}
    virtual void setInterestName(const iName& interestName);
    virtual const iName& getSource() const;
    virtual iName& getSourceForUpdate() { handleChange();return const_cast<iName&>(const_cast<Interest*>(this)->getSource());}
    virtual void setSource(const iName& source);
    virtual unsigned char getType() const;
    virtual void setType(unsigned char type);
    virtual int getHotCount() const;
    virtual void setHotCount(int hotCount);
    virtual short getPrefixLength() const;
    virtual void setPrefixLength(short prefixLength);
    virtual bool getFlood() const;
    virtual void setFlood(bool flood);
    virtual bool getCanBePrefix() const;
    virtual void setCanBePrefix(bool canBePrefix);
    virtual bool getMustBeFresh() const;
    virtual void setMustBeFresh(bool MustBeFresh);
    virtual omnetpp::simtime_t getInterestLifeTime() const;
    virtual void setInterestLifeTime(omnetpp::simtime_t InterestLifeTime);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
    virtual const Port_t& getPortNumber1() const;
    virtual Port_t& getPortNumber1ForUpdate() { handleChange();return const_cast<Port_t&>(const_cast<Interest*>(this)->getPortNumber1());}
    virtual void setPortNumber1(const Port_t& portNumber1);
    virtual const Port_t& getPortNumber2() const;
    virtual Port_t& getPortNumber2ForUpdate() { handleChange();return const_cast<Port_t&>(const_cast<Interest*>(this)->getPortNumber2());}
    virtual void setPortNumber2(const Port_t& portNumber2);
    virtual uint16_t getMTU() const;
    virtual void setMTU(uint16_t MTU);
    virtual uint16_t getChecksum() const;
    virtual void setChecksum(uint16_t checksum);
    virtual long getNonce() const;
    virtual void setNonce(long Nonce);
    virtual const MacAddress& getMAC() const;
    virtual MacAddress& getMACForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<Interest*>(this)->getMAC());}
    virtual void setMAC(const MacAddress& MAC);
    virtual uint16_t getTotalLength() const;
    virtual void setTotalLength(uint16_t totalLength);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Interest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Interest& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_INTEREST_M_H

