//
// This library is free software, you can redistribute it
// and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
//  ; in case hello interest timed out, router will try 'hello-retries' times at 'hello-timeout'
//  ; seconds interval before giving up for any neighbors (deciding link is down)

//   hello-retries 3                     ; interest retries number in integer. Default value 3
//                                       ; valid values 1-10

//   hello-timeout 1                     ; interest time out value in seconds. Default value 1
//                                       ; Valid values 1-15

//   hello-interval  60                  ; interest sending interval in seconds. Default value 60
 //                                      ; valid values 30-90

package inet.routing.nlsr;

@namespace(inet::nlsr);

import inet.routing.contract.Inlsr;

//
// Implements the nlsr routing protocol.
//
// The nlsrConfig parameter can specify an XML file describing the
// configuration of all nlsr routers and their interfaces in the network.
//
// The XML configuration must contain exactly one <nlsrASConfig> root element which

simple Nlsr like Inlsr
{
    parameters:
        string interfaceTableModule="";
        string routingTableModule="";
        string contentStoreModule="";
        string forwardingModule="";
        volatile double startupTime @unit(s) = default(0s); // delay before starting nlsr
        // xml containing the full nlsr configuration
        xml nlsrConfig = default(xml("<NLSRConfig> \
                <Router name='**'> \
                    <PointToPointInterface ifName='eth[*]' interfaceOutputCost='1' /> \
                </Router> </NLSRConfig>"));

        // default values for attributes of interface xml entries:
        int helloInterval @unit(s) = default(3s);  // interest sending interval in seconds. Valid values 1-15
        int routerDeadInterval @unit(s) = 3*helloInterval;//default(10s);  // the interval during which at least one hello packet must be received from a neighbor before the router declares that neighbor as down
        int interfaceTransmissionDelay @unit(s) = default(1s);  // The number of seconds required to transmit a link state update packet. Valid values are 1 to 65535
        string interfaceMode @enum("ACTIVE","PASSIVE","NO_NLSR") = default("ACTIVE");                                                                                   // Passive: the interface is advertised, but no OSPF message is send out
        int interfaceOutputCost = default(2);  // cost of link on the interface (1-1000), 0 means use reference bandwidth
        int linkCost = default(1);  // cost of link (1-1000) for HostInterface and LoopbackInterface only      
		int syncInterval = default(1);
		string RCTpath = default("");
		double sendInterval = default(10);
		
        @display("i=block/network2");
    gates:
      	input ifIn @labels(nlsrPacket);
        output ifOut @labels(nlsrPacket);
}

