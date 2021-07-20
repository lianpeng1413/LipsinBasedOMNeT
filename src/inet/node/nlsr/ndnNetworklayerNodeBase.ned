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

package inet.node.nlsr;

import inet.common.MessageDispatcher;
import inet.networklayer.contract.INetworkLayer;
import inet.node.nlsr.ndnNetworklayer;
import inet.node.base.LinkLayerNodeBase2;

module ndnNetworkLayerNodeBase extends LinkLayerNodeBase2
{
    parameters:
        @display("i=abstract/router;bgb=1315.9359,692.818");
        string energyStorageType = default("");
        string energyGeneratorType = default("");
        bool forwarding = default(true);
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        @figure[networkLayer](type=rectangle; pos=250,306; size=1000,130; fillColor=#00ff00; lineColor=#808080; cornerRadius=5; fillOpacity=0.1);
        @figure[networkLayer.title](type=text; pos=1245,311; anchor=ne; text="network layer");

    submodules:
        ndn: ndnNetworklayer {
            parameters:
                @display("p=460.00122,319.85748;q=queue");
        }

        nl: MessageDispatcher {
            parameters:
                @display("p=588.6037,418.78247;b=700,5,,,,1");
        }

    connections allowunconnected:
        ndn.ifIn <-- nl.out++;
        ndn.ifOut --> nl.in++;

        for i=0..numLoInterfaces-1 {
            nl.out++ --> lo[i].upperLayerIn;
            lo[i].upperLayerOut --> nl.in++;
        }

        for i=0..sizeof(ethg)-1 {
            eth[i].upperLayerOut --> nl.in++;
            eth[i].upperLayerIn <-- nl.out++;
        }

}
