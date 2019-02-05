/*
 * extension.cc
 *
 *  Created on: Apr 10, 2018
 *      Author: domin
 */

//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc3 : public cSimpleModule
{
  private:
    int counter;  // Note the counter here

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc3);

void Txc3::initialize()
{
    // Initialize counter to ten. We'll decrement it every time and delete
    // the message when it reaches zero.
    counter = 10;

    // The WATCH() statement below will let you examine the variable under
    // Tkenv. After doing a few steps in the simulation, double-click either
    // `tic' or `toc', select the Contents tab in the dialog that pops up,
    // and you'll find "counter" in the list.

    WATCH(counter);

    if (strcmp("tic", getName()) == 0) {
        EV << "Sending initial message\n";
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");
    }
}

void Txc3::handleMessage(cMessage *msg)
{
    // Increment counter and check value.

    counter--;

    if (counter == 0) {
        // If counter is zero, delete message. If you run the model, you'll
        // find that the simulation will stop at this point with the message
        // "no more events".
        EV << getName() << "'s counter reached zero, deleting message\n";
        delete msg;
    }

    else {
        EV << getName() << "'s counter is " << counter << ", sending back message\n";
        send(msg, "out");
    }
}

//
// Define new Module 4 here
//

class Txc4 : public cSimpleModule
{
  private:
    int counter;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc4);

void Txc4::initialize()
{
    // Initialize the counter with the "limit" module parameter, declared
    // in the NED file (tictoc4.ned).
    counter = par("limit");

    // we no longer depend on the name of the module to decide
    // whether to send an initial message
    //parameter sendMsgOnInit is declared in .ned file

    if (par("sendMsgOnInit").boolValue() == true) {
        EV << "Sending initial message\n";
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");
    }
}

void Txc4::handleMessage(cMessage *msg)
{
    counter--;
    if (counter == 0) {
        EV << getName() << "'s counter reached zero, deleting message\n";
        delete msg;
    }

    else {
        EV << getName() << "'s counter is " << counter << ", sending back message\n";
        send(msg, "out");
    }
}
//
// No Module 5 Definition here
//

//
// Define new Module 6 here
//

class Txc6 : public cSimpleModule
{
  private:
    cMessage *event;  // pointer to the event object which we'll use for timing
    cMessage *tictocMsg;  // variable to remember the message until we send it back

  public:
    Txc6();
    virtual ~Txc6();

  protected:
     virtual void initialize() override;
     virtual void handleMessage(cMessage *msg) override;
 };

 Define_Module(Txc6);

 Txc6::Txc6()
 {
     // Set the pointer to nullptr, so that the destructor won't crash
     // even if initialize() doesn't get called because of a runtime
     // error or user cancellation during the startup process. //
     event = tictocMsg = nullptr;
 }

 Txc6::~Txc6()
 {
     // Dispose of dynamically allocated the objects
     cancelAndDelete(event);
     delete tictocMsg;
 }

 void Txc6::initialize()
 {
     // Create the event object we'll use for timing -- just any ordinary message.
     event = new cMessage("event");
     // No tictoc message yet.
     tictocMsg = nullptr;

     if (strcmp("tic", getName()) == 0) {
         // We don't start right away, but instead send an message to ourselves
         // (a "self-message") -- we'll do the first sending when it arrives
         // back to us, at t=5.0s simulated time.
         EV << "Scheduling first send to t=5.0s\n";
         tictocMsg = new cMessage("tictocMsg");
         scheduleAt(5.0, event);
     }
 }


 void Txc6::handleMessage(cMessage *msg)
 {
     // There are several ways of distinguishing messages, for example by message
     // kind (an int attribute of cMessage) or by class using dynamic_cast
     // (provided you subclass from cMessage). In this code we just check if we
     // recognize the pointer, which (if feasible) is the easiest and fastest
     // method.

     if (msg == event) {
         // The self-message arrived, so we can send out tictocMsg and nullptr out
         // its pointer so that it doesn't confuse us later.

         EV << "Wait period is over, sending back message\n";
         send(tictocMsg, "out");
         tictocMsg = nullptr;
     }

     else {
         // If the message we received is not our self-message, then it must
         // be the tic-toc message arriving from our partner. We remember its
         // pointer in the tictocMsg variable, then schedule our self-message
         // to come back to us in 1s simulated time.

         EV << "Message arrived, starting to wait 1 sec...\n";
         tictocMsg = msg;
         scheduleAt(simTime()+1.0, event);
     }
 }

 //
 // Define new Module 7 here
 //
 class Txc7 : public cSimpleModule
 {
   private:
     cMessage *event;
     cMessage *tictocMsg;
   public:
     Txc7();
     virtual ~Txc7();
   protected:
     virtual void initialize() override;
     virtual void handleMessage(cMessage *msg) override;
 };
 Define_Module(Txc7);
 Txc7::Txc7()
 {
     event = tictocMsg = nullptr;
 }
 Txc7::~Txc7()
 {
     cancelAndDelete(event);
     delete tictocMsg;
 }
 void Txc7::initialize()
 {
     event = new cMessage("event");
     tictocMsg = nullptr;
     if (strcmp("tic", getName()) == 0) {
         EV << "Scheduling first send to t=5.0s\n";
         scheduleAt(5.0, event);
         tictocMsg = new cMessage("tictocMsg");
     }
 }
 void Txc7::handleMessage(cMessage *msg)
 {
     if (msg == event) {
         EV << "Wait period is over, sending back message\n";
         send(tictocMsg, "out");
         tictocMsg = nullptr;
     }
     else {
         // "Lose" the message with 0.1 probability:
         if (uniform(0, 1) < 0.1) {
             EV << "\"Losing\" message\n";
             delete msg;
         }
         else {
             // The "delayTime" module parameter can be set to values like
             // "exponential(5)" (tictoc7.ned, omnetpp.ini), and then here
             // we'll get a different delay every time.
             simtime_t delay = par("delayTime");
             EV << "Message arrived, starting to wait " << delay << " secs...\n";
             tictocMsg = msg;
             scheduleAt(simTime()+delay, event);
         }
     }
 }
