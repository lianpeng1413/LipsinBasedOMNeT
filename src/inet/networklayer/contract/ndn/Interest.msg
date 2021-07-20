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
import inet.common.ProtocolTag;
import inet.common.packet.chunk.Chunk;
import inet.linklayer.common.MacAddress;
import inet.networklayer.contract.ndn.ndnFields;

namespace inet;

class Interest extends FieldsChunk
{
    chunkLength = B(128);
    
    iName interestName;
    iName source;
    
    unsigned char type = 0;
    int hotCount = 0;
    short prefixLength = 1;
    bool flood = false;
    bool canBePrefix = false;
    bool MustBeFresh = false;
    simtime_t InterestLifeTime;		// default omitted
    unsigned int hopLimit = 256;
  
    Port_t portNumber1 = 0;
    Port_t portNumber2 = 0;
    uint16_t MTU = 0;
    uint16_t checksum = 0;
    long Nonce; 
//  	paths trace;
    MacAddress MAC;   //48bits  
    uint16_t totalLength = 0;
    
}