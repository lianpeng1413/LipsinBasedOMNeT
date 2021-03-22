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

package inet.examples.ndnTest;

import inet.common.scenario.ScenarioManager;
import inet.common.misc.ThruputMeteringChannel;
import inet.linklayer.ethernet.EtherHub;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.visualizer.integrated.IntegratedVisualizer;
import inet.node.ndn.ndnNode;

network ndnTest
{
    parameters:
        @display("bgb=396,225;bgg=100,1,grey95");
        int numHosts = default(2);
        int rngNum = default(5);
        double sendInterval = default(0.001);

    types:
        channel C extends ThruputMeteringChannel
        {
            delay = 0.1ms;
            datarate = 10Mbps;
            thruputDisplayFormat = "#N";
        }
    submodules:
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            @display("p=85,69;is=s");
        }
        scenarioManager: ScenarioManager {
            parameters:
                script = default(xml("<scenario/>"));
                @display("p=85,157;is=s");
        }
        consumer: ndnNode {
            parameters:
                @display("p=197,39");
            gates:
                ethg[1];
        }
        provider: ndnNode {
            parameters:
                @display("p=346,151");
            gates:
                ethg[1];
        }
        R1: ndnNode {
            parameters:
                @display("p=176,100");
            gates:
                ethg[3];
        }
        R2: ndnNode {
            parameters:
                @display("p=176,174");
            gates:
                ethg[2];
        }
        R3: ndnNode {
            parameters:
                @display("p=297,97");
            gates:
                ethg[2];
        }
        R4: ndnNode {
            parameters:
                @display("p=297,174");
            gates:
                ethg[3];
        }

    connections:
        R1.ethg[0] <--> C <--> consumer.ethg[0];
        R1.ethg[2] <--> C <--> R2.ethg[1];
        R1.ethg[1] <--> C <--> R3.ethg[1];

        R4.ethg[0] <--> C <--> provider.ethg[0];
        R2.ethg[0] <--> C <--> R4.ethg[2];
        R3.ethg[0] <--> C <--> R4.ethg[1];
}
