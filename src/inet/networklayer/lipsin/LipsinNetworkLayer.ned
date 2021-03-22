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

package inet.networklayer.lipsin;

import inet.common.MessageDispatcher;
import inet.networklayer.contract.INetworkLayer;

//
// Network layer of an LIPSIN Transmit node
//
module LipsinNetworkLayer like INetworkLayer
{
    parameters:
        bool forwarding = default(true);
        string interfaceTableModule;
        int satId = default(0);
        string displayStringTextFormat = default("%i");
        *.interfaceTableModule = default(absPath(interfaceTableModule));
        *.downLinkTableModule = default(absPath(".downLinkTable"));
        *.physicalLinkTableModule = default(absPath(".physicalLinkTable"));
        *.virtualLinkTableModule = default(absPath(".virtualLinkTable"));
        @class(::inet::LipsinNetworkLayer);
        @display("i=block/fork");
    gates:
        input transportIn @labels(INetworkProtocolControlInfo/down);
        output transportOut @labels(INetworkProtocolControlInfo/up);
        input ifIn @labels(INetworkHeader);
        output ifOut @labels(INetworkHeader);
    
    submodules:
        downLinkTable: LipsinLdTable{
            parameters:
                @display("p=100,100;is=s");
                tableName = "downLinkTable";
        }
        virtualLinkTable: LipsinLdTable{
            parameters:
                @display("p=100,150;is=s");
                tableName = "upLinkTable";
        }        
        physicalLinkTable: LipsinLdTable{
            parameters:
                @display("p=100,200;is=s");
                tableName = "upLinkTable";
        }
        
        NeighborLinkTable: LipsinNeighborTable{
            parameters:
            	@display("p=100,250;is=s");
        }
        forwarder: <default("LipsinForwarder")> like ILipsin{
            parameters:
                @display("p=200,150;is=queue");
        }
    connections allowunconnected:
        transportIn --> { @display("m=n"); } --> forwarder.transportIn;
        transportOut <-- { @display("m=n"); } <-- forwarder.transportOut;
        
        forwarder.queueIn <-- { @display("m=s"); } <-- ifIn;
        forwarder.queueOut --> { @display("m=s"); } --> ifOut;
        
        
}
