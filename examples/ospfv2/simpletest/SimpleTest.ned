
package inet.examples.ospfv2.simpletest;

import inet.common.misc.ThruputMeteringChannel;
import inet.common.scenario.ScenarioManager;
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
        H1: StandardHost {
            parameters:
                @display("p=250,150;i=device/laptop");
            gates:
                ethg[1];
        }
        N1: EtherHub {
            parameters:
                @display("p=400,150");
            gates:
                ethg[2];
        }
        R1: OspfRouter {
            parameters:
                @display("p=550,150");
                hasStatus = true;
            gates:
                ethg[2];
        }
        R2: OspfRouter {
            parameters:
                @display("p=700,150");
                hasStatus = true;
                hasLipsin = true;
                **.satId = 2;
            gates:
                ethg[3];
                pppg[1];
        }
        R3: OspfRouter {
            parameters:
                @display("p=575,63");
                hasStatus = true;
            gates:
                ethg[2];
        }
        R4: LipsinRouter {
            parameters:
                @display("p=725,63");
                hasStatus = true;
                hasOspf = true;
                hasTrafGen = true;
                **.satId = 4;
            gates:
                ethg[1];
                pppg[1];
                
        }
        N2: EtherHub {
            parameters:
                @display("p=850,150");
            gates:
                ethg[2];
        }
        H2: StandardHost {
            parameters:
                @display("p=1000,150;i=device/laptop");
            gates:
                ethg[1];
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                config = xml("<config>"+
                            "<interface among='H1 R1' address='192.168.1.x' netmask='255.255.255.0' />"+
                            "<interface among='H2 R2' address='192.168.2.x' netmask='255.255.255.0' />"+
                            "<interface among='H3 R3' address='192.168.3.x' netmask='255.255.255.0' />"+
                            "<interface among='H4 R4' address='192.168.4.x' netmask='255.255.255.0' />"+
                            "<interface among='R1 R2' address='192.168.60.x' netmask='255.255.255.0' />"+
                            "<interface among='R2 R3' address='192.168.61.x' netmask='255.255.255.0' />"+
                            "<interface hosts='R2' names='ppp*' address='2.2.2.x' netmask='255.255.255.x'/> "+
                            "<interface hosts='R4' names='ppp*' address='4.4.4.x' netmask='255.255.255.x'/> "+
                            "<route hosts='H1 H2 H3 H4' destination='*' netmask='0.0.0.0' interface='eth0' />"+
                            "</config>");
                addStaticRoutes = false;
                addDefaultRoutes = false;
                @display("p=100,100;is=s");
        }
        scenarioManager: ScenarioManager {
            @display("p=100,200;is=s");
        }
        H3: StandardHost {
            parameters:
                @display("p=518,28");
            gates:
                ethg[1];

        }
        H4: StandardHost {
            parameters:
                @display("p=850,15");
            gates:
                ethg[1];
        }
    connections allowunconnected: 
        H1.ethg[0] <--> C <--> N1.ethg[0];
        N1.ethg[1] <--> C <--> R1.ethg[0];
        R1.ethg[1] <--> C <--> R2.ethg[0];
        R2.ethg[1] <--> C <--> N2.ethg[0];
        N2.ethg[1] <--> C <--> H2.ethg[0];
        R3.ethg[0] <--> C <--> R2.ethg[2];
        R4.pppg[0] <--> C <--> R2.pppg[0];

        H3.ethg[0] <--> C <--> R3.ethg[1];
        H4.ethg[0] <--> C <--> R4.ethg[0];
}

