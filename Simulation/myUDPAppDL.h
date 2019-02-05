#ifndef MYUDPAPPDL_H_
#define MYUDPAPPDL_H_

#include <string.h>
#include <list>
#include "inet/applications/udpapp/UDPBasicApp.h"
#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/NodeOperations.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/InterfaceTable.h"
#include "inet/transportlayer/contract/udp/UDPControlInfo_m.h"

class myUDPAppDL: public inet::UDPBasicApp {
private:

protected:
    int PacketLostDelay = 0;
    int TotalLossPacket = 0;
    double RateLoss = 0;
    simtime_t averageDelay = 0;
    virtual void processPacket(cPacket *msg) override;
    virtual void finish() override;
};



#endif /* MYUDPAPPDL_H_ */
