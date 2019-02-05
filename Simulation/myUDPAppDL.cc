#include "myUDPAppDL.h"

#include <iostream>
#include <string>

Define_Module(myUDPAppDL);

void myUDPAppDL::processPacket(cPacket *msg)
{
    averageDelay = averageDelay + (msg->getArrivalTime() - msg->getCreationTime());

    if ((msg->getArrivalTime() - msg->getCreationTime()) <= 0.15) {
        UDPBasicApp::processPacket(msg);

    } else {
        delete msg;
        PacketLostDelay++;
        return;
    }
}

void myUDPAppDL::finish()
{
    TotalLossPacket = numSent - numReceived;
    RateLoss = (double)TotalLossPacket / numSent;
    averageDelay = averageDelay / numSent;

    recordScalar("Average Packet delay", averageDelay);
    recordScalar("Total packets loss", TotalLossPacket);
    recordScalar("Rate packet loss", RateLoss);
    recordScalar("packets with high delay", PacketLostDelay);
    UDPBasicApp::finish();
}
