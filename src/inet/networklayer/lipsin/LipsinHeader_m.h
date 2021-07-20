//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/lipsin/LipsinHeader.msg.
//

#ifndef __INET_LIPSINHEADER_M_H
#define __INET_LIPSINHEADER_M_H

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

class LipsinHeader;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/networklayer/contract/NetworkHeaderBase_m.h" // import inet.networklayer.contract.NetworkHeaderBase

#include "inet/networklayer/lipsin/bloomFilter/BloomFilterLipsin_m.h" // import inet.networklayer.lipsin.bloomFilter.BloomFilterLipsin

#include "inet/networklayer/lipsin/bloomFilter/BloomParameters_m.h" // import inet.networklayer.lipsin.bloomFilter.BloomParameters

// cplusplus {{
#include<cstdlib>
#include "inet/common/ProtocolGroup.h"
#include "inet/networklayer/lipsin/bloomFilter/BloomFilterLipsin.h"
// }}


namespace inet {

// cplusplus {{
    const B LIPSIN_HEADER_LENGTH = B(120);
// }}

/**
 * Class generated from <tt>inet/networklayer/lipsin/LipsinHeader.msg:37</tt> by nedtool.
 * <pre>
 * class LipsinHeader extends FieldsChunk
 * {
 *     chunkLength = LIPSIN_HEADER_LENGTH;
 *     bool init = false;
 *     uint64_t nonce;
 *     BloomParameters para;
 *     BloomFilterLipsin *preRoute;
 *     BloomFilterLipsin *hadRoute;
 * }
 * </pre>
 */
class INET_API LipsinHeader : public ::inet::FieldsChunk
{
  protected:
    bool init = false;
    uint64_t nonce = 0;
    BloomParameters para;
    BloomFilterLipsin * preRoute = nullptr;
    BloomFilterLipsin * hadRoute = nullptr;

  private:
    void copy(const LipsinHeader& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LipsinHeader&);

  public:
    LipsinHeader();
    LipsinHeader(const LipsinHeader& other);
    virtual ~LipsinHeader();
    LipsinHeader& operator=(const LipsinHeader& other);
    virtual LipsinHeader *dup() const override {return new LipsinHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual bool getInit() const;
    virtual void setInit(bool init);
    virtual uint64_t getNonce() const;
    virtual void setNonce(uint64_t nonce);
    virtual const BloomParameters& getPara() const;
    virtual BloomParameters& getParaForUpdate() { handleChange();return const_cast<BloomParameters&>(const_cast<LipsinHeader*>(this)->getPara());}
    virtual void setPara(const BloomParameters& para);
    virtual const BloomFilterLipsin * getPreRoute() const;
    virtual BloomFilterLipsin * getPreRouteForUpdate() { handleChange();return const_cast<BloomFilterLipsin *>(const_cast<LipsinHeader*>(this)->getPreRoute());}
    virtual void setPreRoute(BloomFilterLipsin * preRoute);
    virtual const BloomFilterLipsin * getHadRoute() const;
    virtual BloomFilterLipsin * getHadRouteForUpdate() { handleChange();return const_cast<BloomFilterLipsin *>(const_cast<LipsinHeader*>(this)->getHadRoute());}
    virtual void setHadRoute(BloomFilterLipsin * hadRoute);

	public:
		virtual void initialize() {
		    	init = true;
		        para.projected_element_count = 50;
                para.false_positive_probability = 0.01 ;
                para.compute_optimal_parameters();
                preRoute = new BloomFilterLipsin(para);
                hadRoute = new BloomFilterLipsin(para);
                nonce = rand();
		}
		virtual bool preRouteContains(int linkID);
		virtual void addLinkToPreRoute(int linkID);
		virtual bool hadRouteContains(int linkID);
		virtual void addLinkToHadRoute(int linkID);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LipsinHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LipsinHeader& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_LIPSINHEADER_M_H

