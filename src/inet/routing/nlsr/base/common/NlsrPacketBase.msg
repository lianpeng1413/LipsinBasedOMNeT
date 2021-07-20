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
import inet.networklayer.contract.ndn.ndnFields;

namespace inet::nlsr;

cplusplus {{
    #include "inet/networklayer/contract/ndn/iName.h"
}}

enum NlsrPacketType
{  
    HELLO_INTEREST       = 7;
    HELLO_DATA           = 8;  
    SYNC_INTEREST        = 9;
    SYNC_DATA            = 10;    
    ADJ_LSA_INTEREST     = 11;
    ADJ_LSA_DATA         = 12; 
    NAME_LSA_INTEREST    = 13;
    NAME_LSA_DATA        = 14;
}

//
// Represents an NLSR packet header
//
class NlsrPacketBase extends FieldsChunk
{
    chunkLength = B(48);
    
	iName interestName;   // interst name
    short version = -1;     // 1 byte
    NlsrPacketType type = static_cast<NlsrPacketType>(-1);    // 1 byte
    int packetLengthField;  // 2 bytes
//    int areaID;     // 4 bytes
}
