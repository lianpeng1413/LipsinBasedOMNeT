/*
 * iblt.h
 *
 *  Created on: Sep 3, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_PSYNC_DETAIL_IBLT_H_
#define INET_ROUTING_NLSR_PSYNC_DETAIL_IBLT_H_

#include <inttypes.h>
#include <set>
#include <vector>
#include <string>
#include <memory>

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/PSync/detail/util.h"

namespace inet {
namespace nlsr {

class HashTableEntry
{
public:
    int32_t count;
    uint32_t keySum;
    uint32_t keyCheck;
//    CompressionScheme m_compressionScheme;

    bool isPure() const;

    bool isEmpty() const;
};

extern const size_t N_HASH;
extern const size_t N_HASHCHECK;

/** Invertible Bloom Lookup Table (Invertible Bloom Filter). Used by Partial Sync (PartialProducer) and Full Sync (Full Producer) */
class IBLT
{
public:
  std::vector<HashTableEntry> m_hashTable;

private:
  void update(short plusOrMinus, uint32_t key);

  static const short INSERT = 1;
  static const short ERASE = -1;

public:
  IBLT();
  ~IBLT();
  /**constructor
   * @param expectedNumEntries the expected number of entries in the IBLT*/
  explicit IBLT(size_t expectedNumEntries);

  void insert(uint32_t key);

  void erase(uint32_t key);

  /**@brief List all the entries in the IBLT.
   * This is called on a difference of two IBLTs: ownIBLT - rcvdIBLT
   * Entries listed in positive are in ownIBLT but not in rcvdIBLT
   * Entries listed in negative are in rcvdIBLT but not in ownIBLT
   *
   * @return whether decoding completed successfully
   */
  bool listEntries(std::set<uint32_t>& positive, std::set<uint32_t>& negative) const;

  IBLT operator-(const IBLT& other) const;

  const std::vector<HashTableEntry>& getHashTable() const { return m_hashTable; }

};

bool operator==(const IBLT& iblt1, const IBLT& iblt2);

bool operator!=(const IBLT& iblt1, const IBLT& iblt2);

std::ostream& operator<<(std::ostream& out, const IBLT& iblt);

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_PSYNC_DETAIL_IBLT_H_ */
