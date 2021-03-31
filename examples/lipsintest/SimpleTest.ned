
package inet.examples.lipsintest;

import inet.common.misc.ThruputMeteringChannel;
import inet.common.scenario.ScenarioManager;
import inet.common.scenario.SatScenarioManager;
import inet.linklayer.ethernet.EtherHub;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import inet.node.ospfv2.OspfRouter;
import inet.node.lipsin.LipsinRouter;

network SimpleTest
{
    parameters:
        @display("p=10,10;b=712,152");
    types:
        channel C extends ThruputMeteringChannel
        {
            delay = 0.1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "#N";
        }
    submodules:
         R1: LipsinRouter {
            parameters:
                @display("p=288,58");
                hasStatus = true;
                hasTrafGen = true;
                **.satId = 1;
            gates:
                pppg[2];

        }
        R2: LipsinRouter {
            parameters:
                @display("p=288,214");
                hasStatus = true;
                **.satId = 2;
            gates:
                pppg[2];

        }
        R3: LipsinRouter {
            parameters:
                @display("p=494,214");
                hasStatus = true;
                **.satId = 3;
            gates:
                pppg[2];

        }
        R4: LipsinRouter {
            parameters:
                @display("p=494,58");
                hasStatus = true;
                **.satId = 4;
            gates:
                pppg[2];

        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                config = xml("<config>"+
                            "<interface among='R1 R2' address='192.168.1.x' netmask='255.255.255.0' />"+
                            "<interface among='R2 R3' address='192.168.2.x' netmask='255.255.255.0' />"+
                            "<interface among='R3 R4' address='192.168.3.x' netmask='255.255.255.0' />"+
                            "<interface among='R1 R4' address='192.168.4.x' netmask='255.255.255.0' />"+
                            "</config>");
                addStaticRoutes = false;
                addDefaultRoutes = false;
                @display("p=100,100;is=s");
        }
        scenarioManager: SatScenarioManager {
            @display("p=100,200;is=s");
        }

    connections allowunconnected:
        R1.pppg[0] <--> C <--> R4.pppg[0];
        R1.pppg[1] <--> C <--> R2.pppg[1];
        R2.pppg[0] <--> C <--> R3.pppg[0];
        R3.pppg[1] <--> C <--> R4.pppg[1];
}

