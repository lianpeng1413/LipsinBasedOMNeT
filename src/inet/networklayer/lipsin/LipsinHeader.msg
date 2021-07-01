//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;
import inet.networklayer.contract.NetworkHeaderBase;
import inet.networklayer.lipsin.bloomFilter.BloomFilter;
import inet.networklayer.lipsin.bloomFilter.BloomParameters;


cplusplus {{
#include<cstdlib>
#include "inet/common/ProtocolGroup.h"
#include "inet/networklayer/lipsin/bloomFilter/BloomFilter.h"
}}

namespace inet;

cplusplus{{
    const B LIPSIN_HEADER_LENGTH = B(120);

}}

class LipsinHeader extends FieldsChunk
{
    chunkLength = LIPSIN_HEADER_LENGTH;
    bool init = false;
    uint64_t nonce;
    BloomParameters para;
    BloomFilter* preRoute;
    BloomFilter* hadRoute;
}

cplusplus(LipsinHeader){{
	public:
		virtual void initialize() {
		    	init = true;
		        para.projected_element_count = 50;
                para.false_positive_probability = 0.01 ;
                para.compute_optimal_parameters();
                preRoute = new BloomFilter(para);
                hadRoute = new BloomFilter(para);
                nonce = rand();
		}
		virtual bool preRouteContains(int linkID);
		virtual void addLinkToPreRoute(int linkID);
		virtual bool hadRouteContains(int linkID);
		virtual void addLinkToHadRoute(int linkID);
}}