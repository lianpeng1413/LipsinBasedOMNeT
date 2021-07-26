//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/ndn/NFD/ndnAppData.msg.
//

#ifndef __INET_NDNAPPDATA_M_H
#define __INET_NDNAPPDATA_M_H

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

class ndnAppData;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/ProtocolTag_m.h" // import inet.common.ProtocolTag

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/ndn/NFD/ndnAppData.msg:23</tt> by nedtool.
 * <pre>
 * class ndnAppData extends FieldsChunk
 * {
 *     string data;
 * }
 * </pre>
 */
class INET_API ndnAppData : public ::inet::FieldsChunk
{
  protected:
    omnetpp::opp_string data;

  private:
    void copy(const ndnAppData& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ndnAppData&);

  public:
    ndnAppData();
    ndnAppData(const ndnAppData& other);
    virtual ~ndnAppData();
    ndnAppData& operator=(const ndnAppData& other);
    virtual ndnAppData *dup() const override {return new ndnAppData(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getData() const;
    virtual void setData(const char * data);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ndnAppData& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ndnAppData& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_NDNAPPDATA_M_H
