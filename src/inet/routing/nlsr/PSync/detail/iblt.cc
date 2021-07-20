/*
 * iblt.cc
 *
 *  Created on: Sep 3, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_PSYNC_DETAIL_IBLT_CC_
#define INET_ROUTING_NLSR_PSYNC_DETAIL_IBLT_CC_

#include "inet/routing/nlsr/PSync/detail/iblt.h"
#include <boost/endian/conversion.hpp>

namespace inet {
namespace nlsr {

const size_t N_HASH(3);
const size_t N_HASHCHECK(11);

bool HashTableEntry::isPure() const
{
    if (count == 1 || count == -1) {
        uint32_t check = murmurHash3(N_HASHCHECK, keySum);
        return keyCheck == check;
    }

    return false;
}

bool HashTableEntry::isEmpty() const
{
    return count == 0 && keySum == 0 && keyCheck == 0;
}

IBLT::IBLT() = default;

IBLT::~IBLT()
{
}

IBLT::IBLT(size_t expectedNumEntries)
{
    // 1.5x expectedNumEntries gives very low probability of decoding failure
    size_t nEntries = expectedNumEntries + expectedNumEntries / 2;
    // make nEntries exactly divisible by N_HASH
    size_t remainder = nEntries % N_HASH;
    if (remainder != 0) {
        nEntries += (N_HASH - remainder);
    }

    m_hashTable.resize(nEntries);
}

void IBLT::update(short plusOrMinus, uint32_t key)
{
    size_t bucketsPerHash = m_hashTable.size() / N_HASH;

    for (size_t i = 0; i < N_HASH; i++) {
        size_t startEntry = i * bucketsPerHash;
        uint32_t h = murmurHash3(i, key);
//        std::cout<<startEntry  << ", " << bucketsPerHash << ", m_hashTable value:" << h <<endl;
        HashTableEntry& entry = m_hashTable.at(startEntry + (h % bucketsPerHash));
        entry.count += plusOrMinus;
        entry.keySum ^= key;
        entry.keyCheck ^= murmurHash3(N_HASHCHECK, key);
    }
}

void IBLT::insert(uint32_t key) { update(INSERT, key); }
void IBLT::erase(uint32_t key) { update(ERASE, key); }

bool IBLT::listEntries(std::set<uint32_t>& positive, std::set<uint32_t>& negative) const
{
    IBLT peeled = *this;

    size_t nErased = 0;
    do {
        nErased = 0;
        for (const auto& entry : peeled.m_hashTable) {
            if (entry.isPure()) {
                if (entry.count == 1) {
                    positive.insert(entry.keySum);
                }
                else {
                    negative.insert(entry.keySum);
                }
                peeled.update(-entry.count, entry.keySum);
                ++nErased;
            }
        }
    } while (nErased > 0);

    // If any buckets for one of the hash functions is not empty,
    // then we didn't peel them all:
    for (const auto& entry : peeled.m_hashTable) {
        if (entry.isEmpty() != true) {
            return false;
        }
    }

    return true;
}

IBLT IBLT::operator-(const IBLT& other) const
{
    ASSERT(m_hashTable.size() == other.m_hashTable.size());

    IBLT result(*this);
    for (size_t i = 0; i < m_hashTable.size(); i++) {
        HashTableEntry& e1 = result.m_hashTable.at(i);
        const HashTableEntry& e2 = other.m_hashTable.at(i);
        e1.count -= e2.count;
        e1.keySum ^= e2.keySum;
        e1.keyCheck ^= e2.keyCheck;
  }

  return result;
}

bool operator==(const IBLT& iblt1, const IBLT& iblt2)
{
    auto iblt1HashTable = iblt1.getHashTable();
    auto iblt2HashTable = iblt2.getHashTable();
    if (iblt1HashTable.size() != iblt2HashTable.size()) {
        return false;
    }

    size_t N = iblt1HashTable.size();

    for (size_t i = 0; i < N; i++) {
        if (iblt1HashTable[i].count != iblt2HashTable[i].count ||
                iblt1HashTable[i].keySum != iblt2HashTable[i].keySum ||
                iblt1HashTable[i].keyCheck != iblt2HashTable[i].keyCheck)
            return false;
    }

    return true;
}

bool operator!=(const IBLT& iblt1, const IBLT& iblt2)
{
    return !(iblt1 == iblt2);
}

std::ostream& operator<<(std::ostream& out, const IBLT& iblt)
{
    out << "count keySum keyCheckMatch\n";
    for (const auto& entry : iblt.getHashTable()) {
        out << entry.count << " " << entry.keySum << " ";
        out << ((murmurHash3(N_HASHCHECK, entry.keySum) == entry.keyCheck) ||
                (entry.isEmpty())? "true" : "false");
        out << "\n";
  }

    return out;
}

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_PSYNC_DETAIL_IBLT_CC_ */
