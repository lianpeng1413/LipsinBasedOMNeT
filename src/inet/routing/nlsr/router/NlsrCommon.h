/*
 * NlsrComm.h
 *
 *  Created on: Aug 19, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_NLSRCOMMON_H_
#define INET_ROUTING_NLSR_ROUTER_NLSRCOMMON_H_

#include <ctype.h>
#include <functional>
#include <stdio.h>

#include "inet/common/INETDefs.h"
#include "inet/common/Units_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/contract/ndn/iName.h"

namespace inet {

namespace nlsr {

// global constants
#define LSA_REFRESH_TIME                       1800
#define MAX_AGE                                3600
#define LSA_INTEREST_LIFETIME                  4
#define SYNC_INTEREST_LIFETIME                 60000
#define ADJ_LSA_BUILD_INTERVAL                 10
#define ROUTING_CALC_INTERVAL                  15

#define MAX_AGE                                3600
#define MAX_AGE_DIFF                           900
#define DEFAULT_DESTINATION_ADDRESS            0
#define INITIAL_SEQUENCE_NUMBER                -2147483647
#define MAX_SEQUENCE_NUMBER                    2147483647

#define POINTTOPOINT_LINK_TTL                  255

const B NDN_DATAGRAM_LENGTH                    = B(65536);

const B NLSR_HEADER_LENGTH                     = B(80);
const B NLSR_HELLO_INTEREST_LENGTH             = B(100);
const B NLSR_HELLO_DATA_LENGTH                 = B(100);

const B NLSR_SYNC_INTEREST_LENGTH              = B(1300);
const B NLSR_SYNC_DATA_LENGTH                  = B(1300);
const B NLSR_LSA_HEADER_LENGTH                 = B(80);
const B NLSR_ADJLSA_INTEREST_LENGTH            = B(1000);
const B NLSR_ADJLSA_DATA_LENGTH                = B(1000);
const B NLSR_NAMELSA_INTEREST_LENGTH           = B(1000);
const B NLSR_NAMELSA_DATA_LENGTH               = B(1000);

const B INAME_LENGTH        = B(16);

typedef double Metric;

enum AuthenticationType {
    NULL_TYPE = 0,
    SIMPLE_PASSWORD_TYPE = 1,
    CRYTOGRAPHIC_TYPE = 2
};

enum {
  SYNC_PROTOCOL_CHRONOSYNC = 0,
  SYNC_PROTOCOL_PSYNC = 1
};

struct AuthenticationKeyType
{
    char bytes[8];
};

typedef iName  RouterName;
typedef iName LinkStateId;
typedef int AreaId;
const AreaId BACKBONE_AREAID(0);

struct HostRouteParameters
{
    unsigned char ifIndex;
    Metric linkCost;
};


using std::bind;
//using std::make_shared;
//using std::shared_ptr;
using std::function;

template<typename T, typename = void>
struct is_iterator
{
   static constexpr bool value = false;
};

/*! Use C++11 iterator_traits to check if some type is an iterator
 */
template<typename T>
struct is_iterator<T, typename std::enable_if<!std::is_same<
  typename std::iterator_traits<T>::value_type,
  void>::value>::type>
{
   static constexpr bool value = true;
};

} // namespace nlsr

} // namespace inet

#endif /* INET_ROUTING_NLSR_ROUTER_NLSRCOMMON_H_ */
