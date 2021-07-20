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

package inet.applications.ICNapp;
import inet.applications.contract.IApp;

simple fileTransProvider like IApp
{
    parameters:
        string prefix = default("");  //name prefix
        int port = default(8709);
		volatile double fileSize @unit(B);  // length of full a file in bytes
        int pktLen = default(1000);
        string RSpath = default(""); 
        double startTime @unit(s) = default(3s); // send first packet generate at startTime
        double stopTime @unit(s) = default(-1s); // time to finish sending, negative values mean forever

        @display("i=block/app");
        @lifecycleSupport;
        double stopOperationExtraTime @unit(s) = default(-1s);    // extra time after lifecycle stop operation finished
        double stopOperationTimeout @unit(s) = default(2s);    // timeout value for lifecycle stop operation

    gates:
        input pingIn;
        input socketIn @labels(ITransportPacket/up);
        output socketOut @labels(ITransportPacket/down);
}