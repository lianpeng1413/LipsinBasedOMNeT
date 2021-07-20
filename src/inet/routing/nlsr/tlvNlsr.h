/*
 * tlvNlsr.h
 *
 *  Created on: Jul 13, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NDNSIM_NLSR_BASE_TLVNLSR_H_
#define INET_ROUTING_NDNSIM_NLSR_BASE_TLVNLSR_H_

namespace ndn{
namespace tlv{
namespace nlsr{

// LSDB DataSet
enum {
  LsaInfo          = 128,
  OriginRouter     = 129,
  SequenceNumber   = 130,
  AdjacencyLsa     = 131,
  Adjacency        = 132,
  CoordinateLsa    = 133,
  Double           = 134,
  HyperbolicRadius = 135,
  HyperbolicAngle  = 136,
  NameLsa          = 137,
  LsdbStatus       = 138,
  ExpirationPeriod = 139,
  Cost             = 140,
  Uri              = 141
};

} // namespace nlsr
} // namespace tlv
} // namespace ndn



#endif /* INET_ROUTING_NDNSIM_NLSR_BASE_TLVNLSR_H_ */
