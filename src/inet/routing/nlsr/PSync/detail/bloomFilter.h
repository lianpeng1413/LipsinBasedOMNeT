/*
 * bloomFilter.h
 *
 *  Created on: Sep 3, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_PSYNC_DETAIL_BLOOMFILTER_H_
#define INET_ROUTING_NLSR_PSYNC_DETAIL_BLOOMFILTER_H_

#include <string>
#include <cmath>
#include <cstdlib>
#include <inttypes.h>
#include <set>
#include <vector>

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/PSync/detail/util.h"

namespace inet {
namespace nlsr {

struct optimal_parameters_t
{
    optimal_parameters_t(): number_of_hashes(0),  table_size(0) {}

    unsigned int number_of_hashes;
    unsigned int table_size;
};

class BloomParameters
{
public:
    BloomParameters();

    bool compute_optimal_parameters();

    bool operator!() const
    {
        return (minimum_size > maximum_size)      ||
                (minimum_number_of_hashes > maximum_number_of_hashes) ||
                (minimum_number_of_hashes < 1)     ||
                (0 == maximum_number_of_hashes)    ||
                (0 == projected_element_count)     ||
                (false_positive_probability < 0.0) ||
                (std::numeric_limits<double>::infinity() == std::abs(false_positive_probability)) ||
                (0 == random_seed)                 ||
                (0xFFFFFFFFFFFFFFFFULL == random_seed);
  }

    unsigned int           minimum_size;
    unsigned int           maximum_size;
    unsigned int           minimum_number_of_hashes;
    unsigned int           maximum_number_of_hashes;
    unsigned int           projected_element_count;
    double                 false_positive_probability;
    unsigned long long int random_seed;
    optimal_parameters_t   optimal_parameters;
};

class BloomFilter
{
protected:
    typedef uint32_t bloom_type;
    typedef uint8_t cell_type;
    typedef std::vector <cell_type>::iterator Iterator;

private:
    void generate_unique_salt();

    void compute_indices(const bloom_type& hash, std::size_t& bit_index, std::size_t& bit) const;

private:
    std::vector <bloom_type> salt_;
    std::vector <cell_type>  bit_table_;
    unsigned int             salt_count_;
    unsigned int             table_size_; // 8 * raw_table_size;
    unsigned int             raw_table_size_;
    unsigned int             projected_element_count_;
    unsigned int             inserted_element_count_;
    unsigned long long int   random_seed_;
    double                   desired_false_positive_probability_;

public:
    BloomFilter();
    explicit BloomFilter(const BloomParameters& p);
    BloomFilter(unsigned int projected_element_count, double false_positive_probability);
    BloomFilter(unsigned int projected_element_count, double false_positive_probability, const iName& bfName);
    BloomParameters getParameters(unsigned int projected_element_count, double false_positive_probability);

    /** Append our bloom filter to the given name
     * Append the count and false positive probability along with the bloom filter so that producer
     * (PartialProducer) can construct a copy.
     *
     * @param name append bloom filter to this name */
    void appendToName(iName& name) const;

    void clear();

    void insert(const std::string& key);

    bool contains(const std::string& key) const;

    std::vector<cell_type> table() const;

};

bool operator==(const BloomFilter& bf1, const BloomFilter& bf2);

std::ostream& operator<<(std::ostream& out, const BloomFilter& bf);

} // namespace nlsr
} // namespace inet


#endif /* INET_ROUTING_NLSR_PSYNC_DETAIL_BLOOMFILTER_H_ */
