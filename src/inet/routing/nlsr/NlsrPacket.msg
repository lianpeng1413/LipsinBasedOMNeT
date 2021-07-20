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
import inet.routing.nlsr.base.common.NlsrPacketBase;
//import inet.networklayer.contract.ndn.iName;
import inet.networklayer.contract.ndn.ndnFields;

cplusplus {{
    #include <vector>
    #include <list>

    #include "inet/routing/nlsr/router/namePrefixList.h"
    #include "inet/routing/nlsr/PSync/detail/iblt.h"
    #include "inet/routing/nlsr/neighbor/adjacencyList.h"
}}

class inet::nlsr::IBLT
{
    @existingClass;
}

class inet::nlsr::AdjacencyList
{
    @existingClass;
}

class inet::nlsr::NamePrefixList
{
    @existingClass;
}

namespace inet::nlsr;

enum NlsrTimerType {
    INTERFACE_HELLO_TIMER = 0;
    NEIGHBOR_INACTIVITY_TIMER = 1;
    NEIGHBOR_POLL_TIMER = 2;
    DATABASE_AGE_TIMER = 3;
    SYNC_START_TIMER = 4;
};

// Represents an NLSR packet header
class NlsrPacket extends nlsr::NlsrPacketBase
{
   	chunkLength = B(48);
    version = 2;
}

// Represents a nlsr Hello interest packet
class NlsrHelloInterest extends NlsrPacket
{
    chunkLength = B(100);
    type = HELLO_INTEREST;

    short helloInterval = 5;
    double routerDeadInterval = 0;
    
	int hopCount = 0;			            // for stats only   
    long seqNo = 0; 				        // for stats only

    bool canBePrefix = false;				// default omitted
    bool MustBeFresh = false;				// default omitted
    unsigned int interestLifetimeMs = 4000;	// default omitted
    unsigned int hopLimit = 1;				// 256 = omitted
}

// Represents a nlsr Hello data packet
class NlsrHelloData extends NlsrPacket
{
    chunkLength = B(100);
    type = HELLO_DATA;
    double routerDeadInterval = 0;
    int hopCount = 0;			           // for stats only   
    long seqNo = 0; 				       // for stats only
	unsigned int hopLimit = 1;			   // 256 = omitted
}

// Represents a nlsr sync interest packet. it should add IBF infor.
class syncInterest extends NlsrPacket
{
    chunkLength = B(1300);
    type = SYNC_INTEREST;
    inet::nlsr::IBLT m_iblt;                           // IBLT infor 
    long seqNo = 0; 			           // for stats only
    unsigned int interestLifetimeMs = 4000;	// default omitted
}

// Represents a nlsr sync data packet
class syncData extends NlsrPacket
{
    chunkLength = B(1300);
    type = SYNC_DATA;
    
    int hopCount = 0;			  
    long seqNo = 0; 				
    iName syncDATA[];
    bool moreFragments = false;
    unsigned int hopLimit = 1;	
    
    long totalLength;
}

enum LinkType
{
    POINTTOPOINT_LINK = 1;
}

// LSA Link section 
class NlsrLink extends cObject
{
    iName linkID;
    unsigned long linkData = 0;
    LinkType type = POINTTOPOINT_LINK;
    unsigned long linkCost = 1;     // TOS 0 metric
}
 
enum NlsrLsaType
{
    ADJ_LSA     = 1;
    COORD_LSA   = 2;    
    NAME_LSA    = 3;	
}

// Represents an NLSR LSA header
class NlsrLsaHeader extends cObject
{    
    iName interestName;
    iName originRouter;
    unsigned short lsAge = 0;
    NlsrLsaType lsType = static_cast<NlsrLsaType>(-1);
   	int hopCount = 0;			            // for stats only   
    unsigned long  seqNo = 0; 				// for stats only
    unsigned int hopLimit = 1;				// 256 = omitted
    uint16_t lsaLength = 0;
}

// common ancestor type for all LSAs
class NlsrLsa extends cObject
{    
    NlsrLsaHeader header;
}

// Represents adj and name LSA
class NlsrAdjLsa extends NlsrLsa
{
	NlsrLsaType lsType = ADJ_LSA;
	inet::nlsr::AdjacencyList* m_adl;         // my neighbor list
}

class NlsrNameLsa extends NlsrLsa
{
	NlsrLsaType lsType = NAME_LSA;
	inet::nlsr::NamePrefixList* m_npl;
}

struct NlsrLsaInterest
{
 	unsigned long lsType;
 	iName interestName;   
}

// Represents a nlsr adj and name interest packet
class AdjLsaInterest extends NlsrPacket
{
    chunkLength = B(1000);
    
	NlsrLsaInterest interests[];
    int hopCount = 0;			            // for stats only 
    unsigned int hopLimit = 1;				// to neighbors 
    long seqNo = 0; 				        // for stats only
    
    bool canBePrefix = false;				// default omitted
    bool MustBeFresh = false;				// default omitted
    unsigned int interestLifetimeMs = 4000;	// default omitted
}

class NameLsaInterest extends NlsrPacket
{
    chunkLength = B(1000);
    
    NlsrLsaInterest interests[];
    int hopCount = 0;			            // for stats only 
    unsigned int hopLimit = 1;				// 256 = omitted
    long seqNo = 0; 				        // for stats only
    
    bool canBePrefix = false;				// default omitted
    bool MustBeFresh = false;				// default omitted
    unsigned int interestLifetimeMs = 4000;	// default omitted
}

// Represents an NLSR data packet
class AdjDataPacket extends NlsrPacket
{
    chunkLength = B(1000);
    NlsrAdjLsa *adjLSA;
  	int hopCount = 0;			            // for stats only 
    unsigned int hopLimit = 1;				// 256 = omitted
}

class NameDataPacket extends NlsrPacket
{
    chunkLength = B(1000);
    NlsrNameLsa *nameLSA;
  	int hopCount = 0;			            // for stats only 
    unsigned int hopLimit = 1;				// 256 = omitted
}

