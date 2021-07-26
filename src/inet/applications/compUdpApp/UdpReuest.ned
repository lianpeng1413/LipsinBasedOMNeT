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

package inet.applications.compUdpApp;

import inet.applications.contract.IApp;

//
// request response client.
//
// This module sends one "packet request" to serverAddress:serverPort at time startTime
// and receives stream from ~UdpResponse.
//
simple UdpRequest like IApp
{
    parameters:
        int localPort = default(-1);  // local port (-1: use ephemeral port)
        double sendInterval = default(1);
        string serverAddress;  // server address
        int serverPort;  // server port
        double startTime @unit(s) = default(1s);
        string RSpath = default("./");
        string packetName = default("udpReq");
        int helloInterval @unit(s) = default(10s);
        @display("i=block/app");
        @lifecycleSupport;
        double stopOperationExtraTime @unit(s) = default(-1s);    // extra time after lifecycle stop operation finished
        double stopOperationTimeout @unit(s) = default(2s);    // timeout value for lifecycle stop operation
        @signal[packetReceived](type=inet::Packet);
 
    gates:
        input socketIn @labels(UdpControlInfo/up);
        output socketOut @labels(UdpControlInfo/down);
}
