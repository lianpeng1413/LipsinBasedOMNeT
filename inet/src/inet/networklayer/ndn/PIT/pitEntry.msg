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
//import inet.common.packet.chunk.Chunk;
import inet.linklayer.common.MacAddress;
import inet.networklayer.contract.ndn.ndnFields;

namespace inet;

class pitEntry extends cObject
{
    inet::iName nidName;
    simtime_t TTL;
    MacAddress mac;
	int interfaceId;
	long Nonce;
    bool served;
    bool isConsumer;
}

cplusplus(pitEntry) {{
  public:
    pitEntry(const iName& name, simtime_t t, MacAddress mac, int interfaceId, long Nonce = 0, bool served = false, bool isconsumer=false): cObject(), nidName(name), TTL(t), mac(mac), interfaceId(interfaceId), Nonce(Nonce), served(served), isConsumer_(isconsumer){}    
}}