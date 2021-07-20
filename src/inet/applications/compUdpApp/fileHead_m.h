//
// Generated file, do not edit! Created by nedtool 5.6 from inet/applications/compUdpApp/fileHead.msg.
//

#ifndef __INET_FILEHEAD_M_H
#define __INET_FILEHEAD_M_H

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

class FileReq;
class FileData;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/ProtocolTag_m.h" // import inet.common.ProtocolTag

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/applications/compUdpApp/fileHead.msg:23</tt> by nedtool.
 * <pre>
 * class FileReq extends FieldsChunk
 * {
 *     chunkLength = B(8);
 *     double seq;
 * }
 * </pre>
 */
class INET_API FileReq : public ::inet::FieldsChunk
{
  protected:
    double seq = 0;

  private:
    void copy(const FileReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const FileReq&);

  public:
    FileReq();
    FileReq(const FileReq& other);
    virtual ~FileReq();
    FileReq& operator=(const FileReq& other);
    virtual FileReq *dup() const override {return new FileReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getSeq() const;
    virtual void setSeq(double seq);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const FileReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, FileReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/applications/compUdpApp/fileHead.msg:29</tt> by nedtool.
 * <pre>
 * class FileData extends FieldsChunk
 * {
 *     chunkLength = B(16);
 *     double seq;
 *     double totalLenth;
 * }
 * </pre>
 */
class INET_API FileData : public ::inet::FieldsChunk
{
  protected:
    double seq = 0;
    double totalLenth = 0;

  private:
    void copy(const FileData& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const FileData&);

  public:
    FileData();
    FileData(const FileData& other);
    virtual ~FileData();
    FileData& operator=(const FileData& other);
    virtual FileData *dup() const override {return new FileData(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getSeq() const;
    virtual void setSeq(double seq);
    virtual double getTotalLenth() const;
    virtual void setTotalLenth(double totalLenth);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const FileData& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, FileData& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_FILEHEAD_M_H

