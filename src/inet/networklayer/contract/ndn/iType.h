/*
 * iType.h
 *
 *  Created on: Aug 20, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_CONTRACT_NDN_ITYPE_H_
#define INET_NETWORKLAYER_CONTRACT_NDN_ITYPE_H_

#include "inet/common/INETDefs.h"
#include "inet/common/Protocol.h"
#include "inet/networklayer/contract/IL3AddressType.h"
#include "inet/networklayer/contract/ndn/iName.h"

namespace inet{
namespace tlv{
/** @brief TYPE numbers defined in NDN Packet Format v0.3
 */
enum : uint32_t {
  Invalid                         = 0,
  Interest                        = 5,
  iData                            = 6,
  iNames                            = 7,
  GenericNameComponent            = 8,
  ImplicitSha256DigestComponent   = 1,
  ParametersSha256DigestComponent = 2,
  CanBePrefix                     = 33,
  MustBeFresh                     = 18,
  ForwardingHint                  = 30,
  Nonce                           = 10,
  InterestLifetime                = 12,
  HopLimit                        = 34,
  ApplicationParameters           = 36,
  InterestSignatureInfo           = 44,
  InterestSignatureValue          = 46,
  MetaInfo                        = 20,
  Content                         = 21,
  SignatureInfo                   = 22,
  SignatureValue                  = 23,
  ContentType                     = 24,
  FreshnessPeriod                 = 25,
  FinalBlockId                    = 26,
  SignatureType                   = 27,
  KeyLocator                      = 28,
  KeyDigest                       = 29,
  SignatureNonce                  = 38,
  SignatureTime                   = 40,
  SignatureSeqNum                 = 42,
  LinkDelegation                  = 31,
  LinkPreference                  = 30,

  NameComponentMin = 1,
  NameComponentMax = 65535,

  AppPrivateBlock1 = 128,
  AppPrivateBlock2 = 32767
};
} //namespace tlv

//class INET_API iType : public IL3AddressType
//{
//  public:
//    static iType INSTANCE;
//    static const iName ALL_ROUTERS_MCAST;
//    iName name;
//
//  public:
//    iType() {}
//    virtual ~iType() {}
//
//    virtual int getAddressBitLength() const override { return name.str().length(); }
//    virtual int getMaxPrefixLength() const override { return name.str().length(); }
//    virtual const Protocol *getNetworkProtocol() const override { return &Protocol::nlsr; }
//
//    virtual L3Address getLinkLocalAddress(const InterfaceEntry *ie) const override { return iName::LOCAL_ADDRESS; }
//};

} // namespace inet


#endif /* INET_NETWORKLAYER_CONTRACT_NDN_ITYPE_H_ */
