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
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.integrated.IntegratedVisualizer;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import ned.DatarateChannel;

network networkFinal
{
    parameters:
        int numMembers;
        @display("bgb=698,403");
		
    types:
        channel CHAP_to_CHRouter extends ned.DatarateChannel
        {
            datarate = 100Mbps;
        }
        channel CHRouter_to_TestlabRouter extends ned.DatarateChannel
        {
            datarate = 8Mbps;
            delay = 10ms;
        }
        channel CHRouter_to_HTTPServer extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = exponential(30ms);
        }
        channel TestlabRouter_to_UDPServer extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = exponential(30ms);
        }
        channel TestlabRouter_to_FTPServer extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = 5ms;
        }

    submodules:
        clusterMember[numMembers]: WirelessHost {
            @display("p=563,345,r,10");
        }
        CH_AccessPoint: AccessPoint {
            @display("p=219,345");
        }
        CH_Router: Router {
            @display("p=219,257");
        }
        Testlab_Router: Router {
            @display("p=219,44");
        }
        SensorCar: WirelessHost {
            @display("p=68,345");
        }
        HTTP_Server: StandardHost {
            @display("p=383,257");
        }
        UDP_Server: StandardHost {
            @display("p=383,130");
        }
        FTP_Server: StandardHost {
            @display("p=383,44");
        }
        IPv4_Configurator: IPv4NetworkConfigurator {
            @display("p=68,46");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=68,111");
        } 
        
    connections:
        CH_AccessPoint.ethg++ <--> CHAP_to_CHRouter <--> CH_Router.ethg++;
        CH_Router.pppg++ <--> CHRouter_to_TestlabRouter <--> Testlab_Router.pppg++;
        CH_Router.ethg++ <--> CHRouter_to_HTTPServer <--> HTTP_Server.ethg++;
        Testlab_Router.ethg++ <--> TestlabRouter_to_UDPServer <--> UDP_Server.ethg++;
        Testlab_Router.ethg++ <--> TestlabRouter_to_FTPServer <--> FTP_Server.ethg++;
}
