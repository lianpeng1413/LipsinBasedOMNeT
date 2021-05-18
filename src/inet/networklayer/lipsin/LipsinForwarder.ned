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


moduleinterface ILipsin
{
    gates:
        input transportIn @labels(ITransportPacket/down);
        output transportOut @labels(ITransportPacket/up);
        input queueIn @labels(INetworkHeader/up);
        output queueOut @labels(INetworkHeader/down);
}

simple LipsinForwarder like ILipsin
{
    parameters:
        string interfaceTableModule;
        string downLinkTableModule;
        string physicalLinkTableModule;
        string virtualLinkTableModule;
        double deletePeriod @unit(s) = default(60s);
        double islCheckInterval @unit(s) = default(10s);
        xml lipsinConfig = default(xmldoc("lipsinConfig.xml"));
        @display("i=block/routing");
        
        
    gates:
        input transportIn @labels(LipsinControlInfo/down);
        output transportOut @labels(LipsinControlInfo/up);
        input queueIn @labels(LipsinHeader,Ieee802Ctrl);
        output queueOut @labels(LipsinHeader,Ieee802Ctrl);
        
}