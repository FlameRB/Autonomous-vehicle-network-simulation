# A network of autonomous vehicle (figure below)


![image](https://user-images.githubusercontent.com/15823161/52301287-65b38400-298a-11e9-81fb-4bf29ebcaae7.png)


# Simulating and Analysis this network
The Cluster Members and the Sensor Car are connected to the Access Point via 802.11g Wireless Local Area Networking (WLAN). The Access Point, the CH Router and the HTTP Server together form the Cluster Head (CH). They are connected over the CH Router via Ethernet connections. Between the Test Lab Router and the CH Router lies a Radio Link, which utilizes the Long Term Evolution (LTE) standard. In the simulated network, this link is simplified as a point-to-point (PPP) radio link. The Test Lab router is connected to an UDP and a FTP Server each via an Ethernet connection. <br />
The Cluster Members need to request in certain time intervals control information from the HTTP Server over WLAN. The HTTP requests and replies have a fixed data size. One of the Cluster Members is also transmitting a very large file using the File Transfer Protocol (FTP) to the FTP Server via the Access Point and the PPP Radio Link. In front of the truck cluster is a Sensor Car, which is capturing 3D model data. The data is continuously sent to the UDP Server via the Access Point and the PPP radio link using UDP. Since the Sensor Car also needs to be aware of the road conditions, it receives data from the UDP Server. The UDP packets should meet certain QoS requirements at all time. The average packet delay for UDP needs to be less than 150 ms. Packets with a higher delay are considered lost and will be added to the number of lost packets. The packet loss should not exceed 10%. <br />

The Sensor Car and the UDP Server are sending with a flexible data rate over UDP. Every 100 ms a packet with a flexible data size between 1000 Byte and 1400 Byte is transmitted. As the Sensor Car is supposed to be capturing 3D models all the time, it is considered to run for the whole simulation. <br />
The cluster member are uniformly distributed in a 30 m x 100 m area behind the Access Point. The position of every Cluster Member is considered to be stationary. The HTTP requests have a fixed size of 200 Byte and are sent periodically every 100 ms after receiving the control information from the HTTP server for the previous HTTP request. The HTTP replies have a fixed size of 400 kB. <br />
One of the Cluster Member assumes the role of a special Cluster Member. Its task is to transmit or receive a large file using FTP, which is working on top of Transmission Control Protocol (TCP). Since the files are considered to be large, the FTP file transfer runs for the whole simulation. The WLAN is based on IEEE 802.11g. The maximum segment size for the TCP connection is set to 1460 Byte. If the TCP and IP headers are considered the maximum packet size is 1500 Byte. <br />
From the network topology it can be assumed that the PPP Link is the bottleneck. The maximum bandwidth of this link is 8 MBit/s and it is most likely to cause problems for the application. The main focus of the analysis will be on that link. Another issue in this network topology can be the number of request/replies of the Cluster Members. For that reason the analysis will also have a focus on the impact of the number of Cluster Members in the network. <br />
For the simulation three di˙erent independent scenarios are considered. In the first scenario the special Cluster Member is not transmitting or receiving any data. This scenario is called the Normal Scenario. In the second scenario the special Cluster Member is transmitting large data to the FTP server. This scenario is called the Upload Scenario. In the last scenario the special Cluster Member is receiving large data from the FTP server. This scenario is called the Download Scenario. All scenarios were simulated with different amounts of Cluster Members/HTTP users and constantly transmitting/receiving UDP packets. <br />
The simulation runs for 500 s, which leads to a reasonable sized confidence intervals. The first 10 s are considered as a warm-up period. This is necessary to ensure that all users are connected to the Access Point and the FTP data transmission reaches a stable throughput. <br />

# Built with
C++ <br />
Matlab

# Author
Nam Do
Louis Yin
