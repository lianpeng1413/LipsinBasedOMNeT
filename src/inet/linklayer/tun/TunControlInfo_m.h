//
// Generated file, do not edit! Created by nedtool 5.6 from inet/linklayer/tun/TunControlInfo.msg.
//

#ifndef __INET_TUNCONTROLINFO_M_H
#define __INET_TUNCONTROLINFO_M_H

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

class TunControlInfo;
class TunOpenCommand;
class TunCloseCommand;
class TunDestroyCommand;
class TunSocketClosedIndication;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs


namespace inet {

/**
 * Enum generated from <tt>inet/linklayer/tun/TunControlInfo.msg:24</tt> by nedtool.
 * <pre>
 * enum TunCommandCode
 * {
 *     TUN_C_OPEN = 1;
 *     TUN_C_CLOSE = 2;
 *     TUN_C_DESTROY = 3;
 *     TUN_C_DATA = 4;
 * }
 * </pre>
 */
enum TunCommandCode {
    TUN_C_OPEN = 1,
    TUN_C_CLOSE = 2,
    TUN_C_DESTROY = 3,
    TUN_C_DATA = 4
};

/**
 * Enum generated from <tt>inet/linklayer/tun/TunControlInfo.msg:32</tt> by nedtool.
 * <pre>
 * enum TunSocketIndication
 * {
 *     TUN_I_CLOSED = 2;
 *     TUN_I_DATA = 4;
 * }
 * </pre>
 */
enum TunSocketIndication {
    TUN_I_CLOSED = 2,
    TUN_I_DATA = 4
};

/**
 * Class generated from <tt>inet/linklayer/tun/TunControlInfo.msg:38</tt> by nedtool.
 * <pre>
 * class TunControlInfo extends cObject
 * {
 * }
 * </pre>
 */
class INET_API TunControlInfo : public ::omnetpp::cObject
{
  protected:

  private:
    void copy(const TunControlInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TunControlInfo&);

  public:
    TunControlInfo();
    TunControlInfo(const TunControlInfo& other);
    virtual ~TunControlInfo();
    TunControlInfo& operator=(const TunControlInfo& other);
    virtual TunControlInfo *dup() const override {return new TunControlInfo(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TunControlInfo& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TunControlInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/tun/TunControlInfo.msg:42</tt> by nedtool.
 * <pre>
 * class TunOpenCommand extends TunControlInfo
 * {
 * }
 * </pre>
 */
class INET_API TunOpenCommand : public ::inet::TunControlInfo
{
  protected:

  private:
    void copy(const TunOpenCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TunOpenCommand&);

  public:
    TunOpenCommand();
    TunOpenCommand(const TunOpenCommand& other);
    virtual ~TunOpenCommand();
    TunOpenCommand& operator=(const TunOpenCommand& other);
    virtual TunOpenCommand *dup() const override {return new TunOpenCommand(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TunOpenCommand& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TunOpenCommand& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/tun/TunControlInfo.msg:46</tt> by nedtool.
 * <pre>
 * class TunCloseCommand extends TunControlInfo
 * {
 * }
 * </pre>
 */
class INET_API TunCloseCommand : public ::inet::TunControlInfo
{
  protected:

  private:
    void copy(const TunCloseCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TunCloseCommand&);

  public:
    TunCloseCommand();
    TunCloseCommand(const TunCloseCommand& other);
    virtual ~TunCloseCommand();
    TunCloseCommand& operator=(const TunCloseCommand& other);
    virtual TunCloseCommand *dup() const override {return new TunCloseCommand(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TunCloseCommand& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TunCloseCommand& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/tun/TunControlInfo.msg:50</tt> by nedtool.
 * <pre>
 * class TunDestroyCommand extends TunControlInfo
 * {
 * }
 * </pre>
 */
class INET_API TunDestroyCommand : public ::inet::TunControlInfo
{
  protected:

  private:
    void copy(const TunDestroyCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TunDestroyCommand&);

  public:
    TunDestroyCommand();
    TunDestroyCommand(const TunDestroyCommand& other);
    virtual ~TunDestroyCommand();
    TunDestroyCommand& operator=(const TunDestroyCommand& other);
    virtual TunDestroyCommand *dup() const override {return new TunDestroyCommand(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TunDestroyCommand& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TunDestroyCommand& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/tun/TunControlInfo.msg:54</tt> by nedtool.
 * <pre>
 * class TunSocketClosedIndication extends TunControlInfo
 * {
 * }
 * </pre>
 */
class INET_API TunSocketClosedIndication : public ::inet::TunControlInfo
{
  protected:

  private:
    void copy(const TunSocketClosedIndication& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TunSocketClosedIndication&);

  public:
    TunSocketClosedIndication();
    TunSocketClosedIndication(const TunSocketClosedIndication& other);
    virtual ~TunSocketClosedIndication();
    TunSocketClosedIndication& operator=(const TunSocketClosedIndication& other);
    virtual TunSocketClosedIndication *dup() const override {return new TunSocketClosedIndication(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TunSocketClosedIndication& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TunSocketClosedIndication& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_TUNCONTROLINFO_M_H

