/*
 * txc2.cc
 *
 *  Created on: Apr 10, 2018
 *      Author: domin
 */

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc2 : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++ //IMPORTANCE
Define_Module(Txc2);

void Txc2::initialize()
{
// Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.

    // Am I Tic or Toc?
    if (strcmp("tic", getName()) == 0) {
        // The `ev' object works like `cout' in C++.
        EV << "Sending initial message\n";
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");
    }
}

void Txc2::handleMessage(cMessage *msg)
{
    // msg->getName() is name of the msg object, here it will be "tictocMsg".
    EV << "Received message `" << msg->getName() << "', sending it out again\n";
    send(msg, "out"); // send out the message
}



