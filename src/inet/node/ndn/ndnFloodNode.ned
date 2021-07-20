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

package inet.node.ndn;

import inet.node.ndn.ndnFloodNetworkLayerNodeBase;
import inet.applications.contract.IApp;
import inet.common.MessageDispatcher;

module ndnFloodNode extends ndnFloodNetworkLayerNodeBase
{
    parameters:
        numLoInterfaces = 0;
        int numApps = default(0);
//        string routingType = default("Nlsr");
        @figure[applicationLayer](type=rectangle; pos=250,6; size=1000,130; lineColor=#808080; cornerRadius=5; fillColor=#ffff00; fillOpacity=0.1);
        @figure[applicationLayer.title](type=text; pos=1245,11; anchor=ne; text="application layer");
        @display("i=device/pocketpc_s;bgb=1290.5299,708.722");
        
    submodules:
        app[numApps]: <> like IApp {
            parameters:
                @display("p=435.10748,92.1975,row,150");
        }
        at: MessageDispatcher {
            parameters:
                @display("p=596.8575,177.925;b=700,5,,,,1");
        }

    connections allowunconnected:
        for i=0..numApps-1 {
            app[i].socketOut --> at.in++;
            app[i].socketIn <-- at.out++;
        }
        at.out++ --> ndnFlood.transportIn;
        at.in++ <-- ndnFlood.transportOut;
}
