//
// Copyright (C) 2005 Andras Babos
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package inet.node.lipsin;

import inet.node.inet.Router;
import inet.applications.generic.IpvxTrafGen;
import inet.applications.generic.IIpvxTrafficGenerator;
import inet.applications.generic.IpvxTrafSink;
//
// An Lipsin router.
//
module LipsinRouter extends Router
{
    parameters:
        hasLipsin = true;
        bool hasTrafGen = default(false);
        bool hasTrafSink = default(true);
        *.hasLipsin = hasLipsin;
        @display("i=device/satellite_vl");
        @display("bgb=1359.225,669.375");
    submodules:
        trafGen: <default("IpvxTrafGen")> like IIpvxTrafficGenerator if hasTrafGen {
            parameters:
                @display("p=1125,226");
        }
        trafSink: <default("IpvxTrafSink")> like IIpvxTrafficGenerator if hasTrafSink {
            parameters:
                @display("p=1250,226");
        }
    connections allowunconnected:
        trafGen.ipOut --> tn.in++ if hasTrafGen;
        trafGen.ipIn <-- tn.out++ if hasTrafGen;
        trafSink.ipOut --> tn.in++ if hasTrafSink;
        trafSink.ipIn <-- tn.out++ if hasTrafSink;
}

