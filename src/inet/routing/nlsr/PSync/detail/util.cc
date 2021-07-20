/*
 * util.cc
 *
 *  Created on: Sep 3, 2020
 *      Author: root
 */

#include "inet/routing/nlsr/PSync/detail/util.h"
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>

namespace inet {
namespace nlsr {

namespace bio = boost::iostreams;

static uint32_t ROTL32 ( uint32_t x, int8_t r )
{
  return (x << r) | (x >> (32 - r));
}

uint32_t murmurHash3(uint32_t nHashSeed, const std::vector<unsigned char>& vDataToHash)
{
  uint32_t h1 = nHashSeed;
  const uint32_t c1 = 0xcc9e2d51;
  const uint32_t c2 = 0x1b873593;

  const size_t nblocks = vDataToHash.size() / 4;

  //----------
  // body
  const uint32_t * blocks = (const uint32_t *)(&vDataToHash[0] + nblocks*4);

  for (size_t i = -nblocks; i; i++) {
    uint32_t k1 = blocks[i];

    k1 *= c1;
    k1 = ROTL32(k1,15);
    k1 *= c2;

    h1 ^= k1;
    h1 = ROTL32(h1,13);
    h1 = h1*5+0xe6546b64;
  }

  //----------
  // tail
  const uint8_t * tail = (const uint8_t*)(&vDataToHash[0] + nblocks*4);

  uint32_t k1 = 0;

  switch (vDataToHash.size() & 3) {
    case 3:
      k1 ^= tail[2] << 16;
//      NDN_CXX_FALLTHROUGH;

    case 2:
      k1 ^= tail[1] << 8;
//      NDN_CXX_FALLTHROUGH;

    case 1:
      k1 ^= tail[0];
      k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
  }

  //----------
  // finalization
  h1 ^= vDataToHash.size();
  h1 ^= h1 >> 16;
  h1 *= 0x85ebca6b;
  h1 ^= h1 >> 13;
  h1 *= 0xc2b2ae35;
  h1 ^= h1 >> 16;

  return h1;
}

uint32_t murmurHash3(uint32_t nHashSeed, const std::string& str)
{
  return murmurHash3(nHashSeed, std::vector<unsigned char>(str.begin(), str.end()));
}

uint32_t murmurHash3(uint32_t nHashSeed, uint32_t value)
{
  return murmurHash3(nHashSeed, std::vector<unsigned char>((unsigned char*)&value,
                     (unsigned char*)&value + sizeof(uint32_t)));
}

//std::shared_ptr<Buffer> compress(const uint8_t* buffer, size_t bufferSize)
//{
//    bio::filtering_streambuf<bio::output> out;
//    bio::filtering_streambuf<bio::input> in;
//
//    in.push(bio::array_source(reinterpret_cast<const char*>(buffer), bufferSize));
//    bio::copy(in, out);
//
//    return out.buf();
//}
//
//std::shared_ptr<Buffer> decompress(const uint8_t* buffer, size_t bufferSize)
//{
//    bio::filtering_streambuf<bio::output> out;
//    bio::filtering_streambuf<bio::input> in;
//
//    in.push(bio::array_source(reinterpret_cast<const char*>(buffer), bufferSize));
//    bio::copy(in, out);
//
//    return out.buf();
//}
} // namespace nlsr
} // namespace inet



