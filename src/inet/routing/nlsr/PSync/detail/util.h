/*
 * util.h
 *
 *  Created on: Sep 3, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_PSYNC_DETAIL_UTIL_H_
#define INET_ROUTING_NLSR_PSYNC_DETAIL_UTIL_H_

#include <inttypes.h>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "inet/networklayer/contract/ndn/iName.h"

namespace inet {
namespace nlsr {

uint32_t murmurHash3(uint32_t nHashSeed, const std::vector<unsigned char>& vDataToHash);

uint32_t murmurHash3(uint32_t nHashSeed, const std::string& str);

uint32_t murmurHash3(uint32_t nHashSeed, uint32_t value);

struct MissingDataInfo
{
    MissingDataInfo(const iName& prefix, uint64_t lowSeq, uint64_t highSeq)
        : prefix(prefix)
        , lowSeq(lowSeq)
        , highSeq(highSeq)
    {}

  iName prefix;
  uint64_t lowSeq;
  uint64_t highSeq;
};

enum class CompressionScheme {
  NONE,
  ZLIB,
  GZIP,
  BZIP2,
  LZMA,
  ZSTD,
#ifdef PSYNC_HAVE_ZLIB
  DEFAULT = ZLIB
#else
  DEFAULT = NONE
#endif
};

using Buffer = std::vector<uint8_t>;

std::shared_ptr<Buffer> compress(const uint8_t* buffer, size_t bufferSize);

std::shared_ptr<Buffer> decompress(const uint8_t* buffer, size_t bufferSize);


} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_PSYNC_DETAIL_UTIL_H_ */
