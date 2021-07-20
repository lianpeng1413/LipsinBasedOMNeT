//
// Generated file, do not edit! Created by nedtool 5.6 from inet/routing/nlsr/NlsrPacket.msg.
//

#ifndef __INET__NLSR_NLSRPACKET_M_H
#define __INET__NLSR_NLSRPACKET_M_H

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
namespace nlsr {

class NlsrPacket;
class NlsrHelloInterest;
class NlsrHelloData;
class syncInterest;
class syncData;
class NlsrLink;
class NlsrLsaHeader;
class NlsrLsa;
class NlsrAdjLsa;
class NlsrNameLsa;
struct NlsrLsaInterest;
class AdjLsaInterest;
class NameLsaInterest;
class AdjDataPacket;
class NameDataPacket;
} // namespace nlsr
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/ProtocolTag_m.h" // import inet.common.ProtocolTag

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/routing/nlsr/base/common/NlsrPacketBase_m.h" // import inet.routing.nlsr.base.common.NlsrPacketBase

#include "inet/networklayer/contract/ndn/ndnFields_m.h" // import inet.networklayer.contract.ndn.ndnFields

// cplusplus {{
    #include <vector>
    #include <list>

    #include "inet/routing/nlsr/router/namePrefixList.h"
    #include "inet/routing/nlsr/PSync/detail/iblt.h"
    #include "inet/routing/nlsr/neighbor/adjacencyList.h"
// }}


namespace inet {
namespace nlsr {

/**
 * Enum generated from <tt>inet/routing/nlsr/NlsrPacket.msg:49</tt> by nedtool.
 * <pre>
 * enum NlsrTimerType
 * {
 *     INTERFACE_HELLO_TIMER = 0;
 *     NEIGHBOR_INACTIVITY_TIMER = 1;
 *     NEIGHBOR_POLL_TIMER = 2;
 *     DATABASE_AGE_TIMER = 3;
 *     SYNC_START_TIMER = 4;
 * }
 * </pre>
 */
enum NlsrTimerType {
    INTERFACE_HELLO_TIMER = 0,
    NEIGHBOR_INACTIVITY_TIMER = 1,
    NEIGHBOR_POLL_TIMER = 2,
    DATABASE_AGE_TIMER = 3,
    SYNC_START_TIMER = 4
};

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:59</tt> by nedtool.
 * <pre>
 * // Represents an NLSR packet header
 * class NlsrPacket extends nlsr::NlsrPacketBase
 * {
 *     chunkLength = B(48);
 *     version = 2;
 * }
 * </pre>
 */
class INET_API NlsrPacket : public ::inet::nlsr::NlsrPacketBase
{
  protected:

  private:
    void copy(const NlsrPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NlsrPacket&);

  public:
    NlsrPacket();
    NlsrPacket(const NlsrPacket& other);
    virtual ~NlsrPacket();
    NlsrPacket& operator=(const NlsrPacket& other);
    virtual NlsrPacket *dup() const override {return new NlsrPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:66</tt> by nedtool.
 * <pre>
 * // Represents a nlsr Hello interest packet
 * class NlsrHelloInterest extends NlsrPacket
 * {
 *     chunkLength = B(100);
 *     type = HELLO_INTEREST;
 * 
 *     short helloInterval = 5;
 *     double routerDeadInterval = 0;
 * 
 *     int hopCount = 0;			            // for stats only   
 *     long seqNo = 0; 				        // for stats only
 * 
 *     bool canBePrefix = false;				// default omitted
 *     bool MustBeFresh = false;				// default omitted
 *     unsigned int interestLifetimeMs = 4000;	// default omitted
 *     unsigned int hopLimit = 1;				// 256 = omitted
 * }
 * </pre>
 */
class INET_API NlsrHelloInterest : public ::inet::nlsr::NlsrPacket
{
  protected:
    short helloInterval = 5;
    double routerDeadInterval = 0;
    int hopCount = 0;
    long seqNo = 0;
    bool canBePrefix = false;
    bool MustBeFresh = false;
    unsigned int interestLifetimeMs = 4000;
    unsigned int hopLimit = 1;

  private:
    void copy(const NlsrHelloInterest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NlsrHelloInterest&);

  public:
    NlsrHelloInterest();
    NlsrHelloInterest(const NlsrHelloInterest& other);
    virtual ~NlsrHelloInterest();
    NlsrHelloInterest& operator=(const NlsrHelloInterest& other);
    virtual NlsrHelloInterest *dup() const override {return new NlsrHelloInterest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual short getHelloInterval() const;
    virtual void setHelloInterval(short helloInterval);
    virtual double getRouterDeadInterval() const;
    virtual void setRouterDeadInterval(double routerDeadInterval);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual long getSeqNo() const;
    virtual void setSeqNo(long seqNo);
    virtual bool getCanBePrefix() const;
    virtual void setCanBePrefix(bool canBePrefix);
    virtual bool getMustBeFresh() const;
    virtual void setMustBeFresh(bool MustBeFresh);
    virtual unsigned int getInterestLifetimeMs() const;
    virtual void setInterestLifetimeMs(unsigned int interestLifetimeMs);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrHelloInterest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrHelloInterest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:84</tt> by nedtool.
 * <pre>
 * // Represents a nlsr Hello data packet
 * class NlsrHelloData extends NlsrPacket
 * {
 *     chunkLength = B(100);
 *     type = HELLO_DATA;
 *     double routerDeadInterval = 0;
 *     int hopCount = 0;			           // for stats only   
 *     long seqNo = 0; 				       // for stats only
 *     unsigned int hopLimit = 1;			   // 256 = omitted
 * }
 * </pre>
 */
class INET_API NlsrHelloData : public ::inet::nlsr::NlsrPacket
{
  protected:
    double routerDeadInterval = 0;
    int hopCount = 0;
    long seqNo = 0;
    unsigned int hopLimit = 1;

  private:
    void copy(const NlsrHelloData& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NlsrHelloData&);

  public:
    NlsrHelloData();
    NlsrHelloData(const NlsrHelloData& other);
    virtual ~NlsrHelloData();
    NlsrHelloData& operator=(const NlsrHelloData& other);
    virtual NlsrHelloData *dup() const override {return new NlsrHelloData(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getRouterDeadInterval() const;
    virtual void setRouterDeadInterval(double routerDeadInterval);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual long getSeqNo() const;
    virtual void setSeqNo(long seqNo);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrHelloData& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrHelloData& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:95</tt> by nedtool.
 * <pre>
 * // Represents a nlsr sync interest packet. it should add IBF infor.
 * class syncInterest extends NlsrPacket
 * {
 *     chunkLength = B(1300);
 *     type = SYNC_INTEREST;
 *     inet::nlsr::IBLT m_iblt;                           // IBLT infor 
 *     long seqNo = 0; 			           // for stats only
 *     unsigned int interestLifetimeMs = 4000;	// default omitted
 * }
 * </pre>
 */
class INET_API syncInterest : public ::inet::nlsr::NlsrPacket
{
  protected:
    inet::nlsr::IBLT m_iblt;
    long seqNo = 0;
    unsigned int interestLifetimeMs = 4000;

  private:
    void copy(const syncInterest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const syncInterest&);

  public:
    syncInterest();
    syncInterest(const syncInterest& other);
    virtual ~syncInterest();
    syncInterest& operator=(const syncInterest& other);
    virtual syncInterest *dup() const override {return new syncInterest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const inet::nlsr::IBLT& getM_iblt() const;
    virtual inet::nlsr::IBLT& getM_ibltForUpdate() { handleChange();return const_cast<inet::nlsr::IBLT&>(const_cast<syncInterest*>(this)->getM_iblt());}
    virtual void setM_iblt(const inet::nlsr::IBLT& m_iblt);
    virtual long getSeqNo() const;
    virtual void setSeqNo(long seqNo);
    virtual unsigned int getInterestLifetimeMs() const;
    virtual void setInterestLifetimeMs(unsigned int interestLifetimeMs);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const syncInterest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, syncInterest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:105</tt> by nedtool.
 * <pre>
 * // Represents a nlsr sync data packet
 * class syncData extends NlsrPacket
 * {
 *     chunkLength = B(1300);
 *     type = SYNC_DATA;
 * 
 *     int hopCount = 0;
 *     long seqNo = 0;
 *     iName syncDATA[];
 *     bool moreFragments = false;
 *     unsigned int hopLimit = 1;
 * 
 *     long totalLength;
 * }
 * </pre>
 */
class INET_API syncData : public ::inet::nlsr::NlsrPacket
{
  protected:
    int hopCount = 0;
    long seqNo = 0;
    iName *syncDATA = nullptr;
    size_t syncDATA_arraysize = 0;
    bool moreFragments = false;
    unsigned int hopLimit = 1;
    long totalLength = 0;

  private:
    void copy(const syncData& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const syncData&);

  public:
    syncData();
    syncData(const syncData& other);
    virtual ~syncData();
    syncData& operator=(const syncData& other);
    virtual syncData *dup() const override {return new syncData(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual long getSeqNo() const;
    virtual void setSeqNo(long seqNo);
    virtual void setSyncDATAArraySize(size_t size);
    virtual size_t getSyncDATAArraySize() const;
    virtual const iName& getSyncDATA(size_t k) const;
    virtual iName& getSyncDATAForUpdate(size_t k) { handleChange();return const_cast<iName&>(const_cast<syncData*>(this)->getSyncDATA(k));}
    virtual void setSyncDATA(size_t k, const iName& syncDATA);
    virtual void insertSyncDATA(const iName& syncDATA);
    virtual void insertSyncDATA(size_t k, const iName& syncDATA);
    virtual void eraseSyncDATA(size_t k);
    virtual bool getMoreFragments() const;
    virtual void setMoreFragments(bool moreFragments);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
    virtual long getTotalLength() const;
    virtual void setTotalLength(long totalLength);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const syncData& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, syncData& obj) {obj.parsimUnpack(b);}

/**
 * Enum generated from <tt>inet/routing/nlsr/NlsrPacket.msg:119</tt> by nedtool.
 * <pre>
 * enum LinkType
 * {
 *     POINTTOPOINT_LINK = 1;
 * }
 * </pre>
 */
enum LinkType {
    POINTTOPOINT_LINK = 1
};

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:125</tt> by nedtool.
 * <pre>
 * // LSA Link section 
 * class NlsrLink extends cObject
 * {
 *     iName linkID;
 *     unsigned long linkData = 0;
 *     LinkType type = POINTTOPOINT_LINK;
 *     unsigned long linkCost = 1;     // TOS 0 metric
 * }
 * </pre>
 */
class INET_API NlsrLink : public ::omnetpp::cObject
{
  protected:
    iName linkID;
    unsigned long linkData = 0;
    inet::nlsr::LinkType type = POINTTOPOINT_LINK;
    unsigned long linkCost = 1;

  private:
    void copy(const NlsrLink& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NlsrLink&);

  public:
    NlsrLink();
    NlsrLink(const NlsrLink& other);
    virtual ~NlsrLink();
    NlsrLink& operator=(const NlsrLink& other);
    virtual NlsrLink *dup() const override {return new NlsrLink(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const iName& getLinkID() const;
    virtual iName& getLinkIDForUpdate() { return const_cast<iName&>(const_cast<NlsrLink*>(this)->getLinkID());}
    virtual void setLinkID(const iName& linkID);
    virtual unsigned long getLinkData() const;
    virtual void setLinkData(unsigned long linkData);
    virtual inet::nlsr::LinkType getType() const;
    virtual void setType(inet::nlsr::LinkType type);
    virtual unsigned long getLinkCost() const;
    virtual void setLinkCost(unsigned long linkCost);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrLink& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrLink& obj) {obj.parsimUnpack(b);}

/**
 * Enum generated from <tt>inet/routing/nlsr/NlsrPacket.msg:133</tt> by nedtool.
 * <pre>
 * enum NlsrLsaType
 * {
 *     ADJ_LSA = 1;
 *     COORD_LSA = 2;
 *     NAME_LSA = 3;
 * }
 * </pre>
 */
enum NlsrLsaType {
    ADJ_LSA = 1,
    COORD_LSA = 2,
    NAME_LSA = 3
};

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:141</tt> by nedtool.
 * <pre>
 * // Represents an NLSR LSA header
 * class NlsrLsaHeader extends cObject
 * {
 *     iName interestName;
 *     iName originRouter;
 *     unsigned short lsAge = 0;
 *     NlsrLsaType lsType = static_cast<NlsrLsaType>(-1);
 *     int hopCount = 0;			            // for stats only   
 *     unsigned long seqNo = 0; 				// for stats only
 *     unsigned int hopLimit = 1;				// 256 = omitted
 *     uint16_t lsaLength = 0;
 * }
 * </pre>
 */
class INET_API NlsrLsaHeader : public ::omnetpp::cObject
{
  protected:
    iName interestName;
    iName originRouter;
    unsigned short lsAge = 0;
    inet::nlsr::NlsrLsaType lsType = static_cast<NlsrLsaType>(-1);
    int hopCount = 0;
    unsigned long seqNo = 0;
    unsigned int hopLimit = 1;
    uint16_t lsaLength = 0;

  private:
    void copy(const NlsrLsaHeader& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NlsrLsaHeader&);

  public:
    NlsrLsaHeader();
    NlsrLsaHeader(const NlsrLsaHeader& other);
    virtual ~NlsrLsaHeader();
    NlsrLsaHeader& operator=(const NlsrLsaHeader& other);
    virtual NlsrLsaHeader *dup() const override {return new NlsrLsaHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const iName& getInterestName() const;
    virtual iName& getInterestNameForUpdate() { return const_cast<iName&>(const_cast<NlsrLsaHeader*>(this)->getInterestName());}
    virtual void setInterestName(const iName& interestName);
    virtual const iName& getOriginRouter() const;
    virtual iName& getOriginRouterForUpdate() { return const_cast<iName&>(const_cast<NlsrLsaHeader*>(this)->getOriginRouter());}
    virtual void setOriginRouter(const iName& originRouter);
    virtual unsigned short getLsAge() const;
    virtual void setLsAge(unsigned short lsAge);
    virtual inet::nlsr::NlsrLsaType getLsType() const;
    virtual void setLsType(inet::nlsr::NlsrLsaType lsType);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual unsigned long getSeqNo() const;
    virtual void setSeqNo(unsigned long seqNo);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
    virtual uint16_t getLsaLength() const;
    virtual void setLsaLength(uint16_t lsaLength);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrLsaHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrLsaHeader& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:154</tt> by nedtool.
 * <pre>
 * // common ancestor type for all LSAs
 * class NlsrLsa extends cObject
 * {
 *     NlsrLsaHeader header;
 * }
 * </pre>
 */
class INET_API NlsrLsa : public ::omnetpp::cObject
{
  protected:
    NlsrLsaHeader header;

  private:
    void copy(const NlsrLsa& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NlsrLsa&);

  public:
    NlsrLsa();
    NlsrLsa(const NlsrLsa& other);
    virtual ~NlsrLsa();
    NlsrLsa& operator=(const NlsrLsa& other);
    virtual NlsrLsa *dup() const override {return new NlsrLsa(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const NlsrLsaHeader& getHeader() const;
    virtual NlsrLsaHeader& getHeaderForUpdate() { return const_cast<NlsrLsaHeader&>(const_cast<NlsrLsa*>(this)->getHeader());}
    virtual void setHeader(const NlsrLsaHeader& header);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrLsa& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrLsa& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:160</tt> by nedtool.
 * <pre>
 * // Represents adj and name LSA
 * class NlsrAdjLsa extends NlsrLsa
 * {
 *     NlsrLsaType lsType = ADJ_LSA;
 *     inet::nlsr::AdjacencyList *m_adl;         // my neighbor list
 * }
 * </pre>
 */
class INET_API NlsrAdjLsa : public ::inet::nlsr::NlsrLsa
{
  protected:
    inet::nlsr::NlsrLsaType lsType = ADJ_LSA;
    inet::nlsr::AdjacencyList * m_adl = nullptr;

  private:
    void copy(const NlsrAdjLsa& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NlsrAdjLsa&);

  public:
    NlsrAdjLsa();
    NlsrAdjLsa(const NlsrAdjLsa& other);
    virtual ~NlsrAdjLsa();
    NlsrAdjLsa& operator=(const NlsrAdjLsa& other);
    virtual NlsrAdjLsa *dup() const override {return new NlsrAdjLsa(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::nlsr::NlsrLsaType getLsType() const;
    virtual void setLsType(inet::nlsr::NlsrLsaType lsType);
    virtual const inet::nlsr::AdjacencyList * getM_adl() const;
    virtual inet::nlsr::AdjacencyList * getM_adlForUpdate() { return const_cast<inet::nlsr::AdjacencyList *>(const_cast<NlsrAdjLsa*>(this)->getM_adl());}
    virtual void setM_adl(inet::nlsr::AdjacencyList * m_adl);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrAdjLsa& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrAdjLsa& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:166</tt> by nedtool.
 * <pre>
 * class NlsrNameLsa extends NlsrLsa
 * {
 *     NlsrLsaType lsType = NAME_LSA;
 *     inet::nlsr::NamePrefixList *m_npl;
 * }
 * </pre>
 */
class INET_API NlsrNameLsa : public ::inet::nlsr::NlsrLsa
{
  protected:
    inet::nlsr::NlsrLsaType lsType = NAME_LSA;
    inet::nlsr::NamePrefixList * m_npl = nullptr;

  private:
    void copy(const NlsrNameLsa& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NlsrNameLsa&);

  public:
    NlsrNameLsa();
    NlsrNameLsa(const NlsrNameLsa& other);
    virtual ~NlsrNameLsa();
    NlsrNameLsa& operator=(const NlsrNameLsa& other);
    virtual NlsrNameLsa *dup() const override {return new NlsrNameLsa(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::nlsr::NlsrLsaType getLsType() const;
    virtual void setLsType(inet::nlsr::NlsrLsaType lsType);
    virtual const inet::nlsr::NamePrefixList * getM_npl() const;
    virtual inet::nlsr::NamePrefixList * getM_nplForUpdate() { return const_cast<inet::nlsr::NamePrefixList *>(const_cast<NlsrNameLsa*>(this)->getM_npl());}
    virtual void setM_npl(inet::nlsr::NamePrefixList * m_npl);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrNameLsa& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrNameLsa& obj) {obj.parsimUnpack(b);}

/**
 * Struct generated from inet/routing/nlsr/NlsrPacket.msg:172 by nedtool.
 */
struct INET_API NlsrLsaInterest
{
    NlsrLsaInterest();
    unsigned long lsType;
    iName interestName;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const NlsrLsaInterest& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, NlsrLsaInterest& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NlsrLsaInterest& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NlsrLsaInterest& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:179</tt> by nedtool.
 * <pre>
 * // Represents a nlsr adj and name interest packet
 * class AdjLsaInterest extends NlsrPacket
 * {
 *     chunkLength = B(1000);
 * 
 *     NlsrLsaInterest interests[];
 *     int hopCount = 0;			            // for stats only 
 *     unsigned int hopLimit = 1;				// to neighbors 
 *     long seqNo = 0; 				        // for stats only
 * 
 *     bool canBePrefix = false;				// default omitted
 *     bool MustBeFresh = false;				// default omitted
 *     unsigned int interestLifetimeMs = 4000;	// default omitted
 * }
 * </pre>
 */
class INET_API AdjLsaInterest : public ::inet::nlsr::NlsrPacket
{
  protected:
    NlsrLsaInterest *interests = nullptr;
    size_t interests_arraysize = 0;
    int hopCount = 0;
    unsigned int hopLimit = 1;
    long seqNo = 0;
    bool canBePrefix = false;
    bool MustBeFresh = false;
    unsigned int interestLifetimeMs = 4000;

  private:
    void copy(const AdjLsaInterest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AdjLsaInterest&);

  public:
    AdjLsaInterest();
    AdjLsaInterest(const AdjLsaInterest& other);
    virtual ~AdjLsaInterest();
    AdjLsaInterest& operator=(const AdjLsaInterest& other);
    virtual AdjLsaInterest *dup() const override {return new AdjLsaInterest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual void setInterestsArraySize(size_t size);
    virtual size_t getInterestsArraySize() const;
    virtual const NlsrLsaInterest& getInterests(size_t k) const;
    virtual NlsrLsaInterest& getInterestsForUpdate(size_t k) { handleChange();return const_cast<NlsrLsaInterest&>(const_cast<AdjLsaInterest*>(this)->getInterests(k));}
    virtual void setInterests(size_t k, const NlsrLsaInterest& interests);
    virtual void insertInterests(const NlsrLsaInterest& interests);
    virtual void insertInterests(size_t k, const NlsrLsaInterest& interests);
    virtual void eraseInterests(size_t k);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
    virtual long getSeqNo() const;
    virtual void setSeqNo(long seqNo);
    virtual bool getCanBePrefix() const;
    virtual void setCanBePrefix(bool canBePrefix);
    virtual bool getMustBeFresh() const;
    virtual void setMustBeFresh(bool MustBeFresh);
    virtual unsigned int getInterestLifetimeMs() const;
    virtual void setInterestLifetimeMs(unsigned int interestLifetimeMs);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AdjLsaInterest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AdjLsaInterest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:193</tt> by nedtool.
 * <pre>
 * class NameLsaInterest extends NlsrPacket
 * {
 *     chunkLength = B(1000);
 * 
 *     NlsrLsaInterest interests[];
 *     int hopCount = 0;			            // for stats only 
 *     unsigned int hopLimit = 1;				// 256 = omitted
 *     long seqNo = 0; 				        // for stats only
 * 
 *     bool canBePrefix = false;				// default omitted
 *     bool MustBeFresh = false;				// default omitted
 *     unsigned int interestLifetimeMs = 4000;	// default omitted
 * }
 * </pre>
 */
class INET_API NameLsaInterest : public ::inet::nlsr::NlsrPacket
{
  protected:
    NlsrLsaInterest *interests = nullptr;
    size_t interests_arraysize = 0;
    int hopCount = 0;
    unsigned int hopLimit = 1;
    long seqNo = 0;
    bool canBePrefix = false;
    bool MustBeFresh = false;
    unsigned int interestLifetimeMs = 4000;

  private:
    void copy(const NameLsaInterest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NameLsaInterest&);

  public:
    NameLsaInterest();
    NameLsaInterest(const NameLsaInterest& other);
    virtual ~NameLsaInterest();
    NameLsaInterest& operator=(const NameLsaInterest& other);
    virtual NameLsaInterest *dup() const override {return new NameLsaInterest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual void setInterestsArraySize(size_t size);
    virtual size_t getInterestsArraySize() const;
    virtual const NlsrLsaInterest& getInterests(size_t k) const;
    virtual NlsrLsaInterest& getInterestsForUpdate(size_t k) { handleChange();return const_cast<NlsrLsaInterest&>(const_cast<NameLsaInterest*>(this)->getInterests(k));}
    virtual void setInterests(size_t k, const NlsrLsaInterest& interests);
    virtual void insertInterests(const NlsrLsaInterest& interests);
    virtual void insertInterests(size_t k, const NlsrLsaInterest& interests);
    virtual void eraseInterests(size_t k);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
    virtual long getSeqNo() const;
    virtual void setSeqNo(long seqNo);
    virtual bool getCanBePrefix() const;
    virtual void setCanBePrefix(bool canBePrefix);
    virtual bool getMustBeFresh() const;
    virtual void setMustBeFresh(bool MustBeFresh);
    virtual unsigned int getInterestLifetimeMs() const;
    virtual void setInterestLifetimeMs(unsigned int interestLifetimeMs);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NameLsaInterest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NameLsaInterest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:208</tt> by nedtool.
 * <pre>
 * // Represents an NLSR data packet
 * class AdjDataPacket extends NlsrPacket
 * {
 *     chunkLength = B(1000);
 *     NlsrAdjLsa *adjLSA;
 *     int hopCount = 0;			            // for stats only 
 *     unsigned int hopLimit = 1;				// 256 = omitted
 * }
 * </pre>
 */
class INET_API AdjDataPacket : public ::inet::nlsr::NlsrPacket
{
  protected:
    NlsrAdjLsa * adjLSA = nullptr;
    int hopCount = 0;
    unsigned int hopLimit = 1;

  private:
    void copy(const AdjDataPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AdjDataPacket&);

  public:
    AdjDataPacket();
    AdjDataPacket(const AdjDataPacket& other);
    virtual ~AdjDataPacket();
    AdjDataPacket& operator=(const AdjDataPacket& other);
    virtual AdjDataPacket *dup() const override {return new AdjDataPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const NlsrAdjLsa * getAdjLSA() const;
    virtual NlsrAdjLsa * getAdjLSAForUpdate() { handleChange();return const_cast<NlsrAdjLsa *>(const_cast<AdjDataPacket*>(this)->getAdjLSA());}
    virtual void setAdjLSA(NlsrAdjLsa * adjLSA);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AdjDataPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AdjDataPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/nlsr/NlsrPacket.msg:216</tt> by nedtool.
 * <pre>
 * class NameDataPacket extends NlsrPacket
 * {
 *     chunkLength = B(1000);
 *     NlsrNameLsa *nameLSA;
 *     int hopCount = 0;			            // for stats only 
 *     unsigned int hopLimit = 1;				// 256 = omitted
 * }
 * </pre>
 */
class INET_API NameDataPacket : public ::inet::nlsr::NlsrPacket
{
  protected:
    NlsrNameLsa * nameLSA = nullptr;
    int hopCount = 0;
    unsigned int hopLimit = 1;

  private:
    void copy(const NameDataPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NameDataPacket&);

  public:
    NameDataPacket();
    NameDataPacket(const NameDataPacket& other);
    virtual ~NameDataPacket();
    NameDataPacket& operator=(const NameDataPacket& other);
    virtual NameDataPacket *dup() const override {return new NameDataPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const NlsrNameLsa * getNameLSA() const;
    virtual NlsrNameLsa * getNameLSAForUpdate() { handleChange();return const_cast<NlsrNameLsa *>(const_cast<NameDataPacket*>(this)->getNameLSA());}
    virtual void setNameLSA(NlsrNameLsa * nameLSA);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual unsigned int getHopLimit() const;
    virtual void setHopLimit(unsigned int hopLimit);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NameDataPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NameDataPacket& obj) {obj.parsimUnpack(b);}

} // namespace nlsr
} // namespace inet

#endif // ifndef __INET__NLSR_NLSRPACKET_M_H

