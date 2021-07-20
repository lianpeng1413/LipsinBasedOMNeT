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
import inet.common.Protocol;
import inet.networklayer.contract.ndn.ndnFields;

namespace inet;

enum ndnCommandCode
{
 	 NDN_C_BIND   = 1;
 	 NDN_C_SEND_INTEREST = 2;
     NDN_C_CLOSE = 3;
     NDN_C_DESTROY = 4;
     NDN_C_CACHE_DATA = 5; 
};

enum ndnStatusInd {
    NDN_I_DATA = 0;
    NDN_I_SOCKET_CLOSED = 1;
};

class ndnSocketCommandBase extends cObject
{
    
}

class ndnSocketBindCommand extends ndnSocketCommandBase
{
    const Protocol *protocol;
    int localPort;
    iName nid;
}

class ndnSocketSendInterestCommand extends ndnSocketCommandBase
{
	iName interest;
    int localPort;
    double Inter;   
}

class ndnSocketCacheDataCommand extends ndnSocketCommandBase
{
	iName interest;
    cMessage *pkt; 
}

class ndnSocketCloseCommand extends ndnSocketCommandBase
{
}

class ndnSocketDestroyCommand extends ndnSocketCommandBase
{
}