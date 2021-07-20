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
import inet.networklayer.ndn.base.ndn;
import inet.networklayer.ndn.CS.cacheTable;
import inet.networklayer.ndn.PIT.pitBase;
import inet.networklayer.ndn.NFD.NFD;
import inet.routing.nlsr.router.route.Fib;
import inet.routing.nlsr.router.route.RoutingTable;
import inet.routing.contract.Inlsr;
import inet.routing.nlsr.Nlsr;

module ndnNetworklayer like INetworkLayer
{
    parameters:
        string nid = default("xxx");
        string interfaceTableModule;
        bool hasNlsr = default(false);
        string routingType = default("Nlsr");
        @display("i=block/fork;bgb=517,260");
    gates:
        input ifIn @labels(INetworkHeader);
        output ifOut @labels(INetworkHeader);
        input transportIn @labels(ndnControlInfo/down);
        output transportOut @labels(ndnControlInfo/up);

    submodules:
        fib: Fib {
            parameters:
                @display("p=52,28;is=s");
        }
        pit: pitBase {
            parameters:
                @display("p=52,85;is=s");
        }
        cs: cacheTable {
            parameters:
                @display("p=52,138;is=s");
        }
        routingTable: RoutingTable {
            parameters:
                @display("p=52,183;is=s");
        }
        nlsr: <routingType> like Inlsr {
            parameters:
                @display("p=382,138;q=pendingQueue");
        }
        up: MessageDispatcher {
            parameters:
                @display("p=306,75;b=400,5");
        }
        lp: MessageDispatcher {
            parameters:
                @display("p=300,213;b=400,5");
        }
        ndnNet: <default("NFD")> like ndn {
            parameters:
                @display("p=209,138;q=queue");
        }

    connections allowunconnected:
        transportIn --> { @display("m=n"); } --> up.in++;
        transportOut <-- { @display("m=n"); } <-- up.out++;

        up.out++ --> ndnNet.transportIn;
        up.in++ <-- ndnNet.transportOut;

        nlsr.ifIn <-- lp.out++;
        nlsr.ifOut --> lp.in++;

        ndnNet.queueOut --> lp.in++;
        ndnNet.queueIn <-- lp.out++;

        lp.out++ --> { @display("m=s"); } --> ifOut;
        lp.in++ <-- { @display("m=s"); } <-- ifIn;
}
