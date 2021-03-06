//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/ndn/FIB/iFib.msg.
//

#ifndef __INET_IFIB_M_H
#define __INET_IFIB_M_H

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

class iFib;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress

#include "inet/networklayer/contract/ndn/ndnFields_m.h" // import inet.networklayer.contract.ndn.ndnFields


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/ndn/FIB/iFib.msg:27</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * class iFib extends cObject
 * {
 *     iName nextHop;
 *     MacAddress nextMac;
 *     simtime_t lifeTime;
 *     int interFace;
 *     double linkQlt;
 * }
 * </pre>
 */
class INET_API iFib : public ::omnetpp::cObject
{
  protected:
    iName nextHop;
    MacAddress nextMac;
    omnetpp::simtime_t lifeTime = SIMTIME_ZERO;
    int interFace = 0;
    double linkQlt = 0;

  private:
    void copy(const iFib& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const iFib&);

  public:
    iFib();
    iFib(const iFib& other);
    virtual ~iFib();
    iFib& operator=(const iFib& other);
    virtual iFib *dup() const override {return new iFib(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const iName& getNextHop() const;
    virtual iName& getNextHopForUpdate() { return const_cast<iName&>(const_cast<iFib*>(this)->getNextHop());}
    virtual void setNextHop(const iName& nextHop);
    virtual const MacAddress& getNextMac() const;
    virtual MacAddress& getNextMacForUpdate() { return const_cast<MacAddress&>(const_cast<iFib*>(this)->getNextMac());}
    virtual void setNextMac(const MacAddress& nextMac);
    virtual omnetpp::simtime_t getLifeTime() const;
    virtual void setLifeTime(omnetpp::simtime_t lifeTime);
    virtual int getInterFace() const;
    virtual void setInterFace(int interFace);
    virtual double getLinkQlt() const;
    virtual void setLinkQlt(double linkQlt);

  public:
    iFib(const iName& next, const MacAddress& mac, const simtime_t& time, int interFace = 0, double link= 1.0): cObject(), nextHop(next), nextMac(mac), lifeTime(time), interFace(interFace), linkQlt(link){}

    //???????????????????????????????????????
    bool comparator(iFib& c1, iFib& c2)
    {
        if(c1.nextHop == c2.nextHop && c1.nextMac == c2.nextMac)
            return true;
        else return false;
    }
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const iFib& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, iFib& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_IFIB_M_H

