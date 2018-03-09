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

#include <string.h>
#include <omnetpp.h>
#include "msgpacket_m.h"
#include "starting_node.h"

Define_Module(Starting_node);

void Starting_node::initialize()
{
    gIn = gate("in");
    gOut = gate("out");
    address = par("id");
    sourc = par("src");
    dest = par("dest");
    counter = 10;

    if(address == sourc)
    {
        cMessage* event = new cMessage();
        scheduleAt(0, event);
        counter--;
    }
}

void Starting_node::handleMessage(cMessage *msg)
{
    //Self-Message Handling
    if(msg -> isSelfMessage())
    {
        Msgpacket* msg_new = new Msgpacket();
        msg_new->setType("Data");
        msg_new->setId(1);
        msg_new->setSource_address(sourc);
        msg_new->setDestination_address(dest);
        send (msg_new, gOut);

        counter--;
        EV << "\nData Sent!";
    }

    //Inter-Message Handling
    else
    {
        Msgpacket* msg_pkt = check_and_cast<Msgpacket *>(msg);

        //If Destination Address != Current NodeID
        if(msg_pkt->getDestination_address() != address)
        {
            send (msg_pkt, gOut);
        }

        //If Destination Address = Current NodeID
        if(msg_pkt->getDestination_address() == address)
        {
            if (counter >= 0)
            {
                if (strcmp(msg_pkt->getType(),"Data")==0)
                {
                    EV << "\nData Received!";

                    Msgpacket* msg_new = new Msgpacket();
                    msg_new->setType("Ack");
                    msg_new->setId(2);
                    msg_new->setSource_address(address);
                    msg_new->setDestination_address(msg_pkt->getSource_address());
                    send (msg_new, gOut);

                    EV << "\nAcknowledgement Sent!";
                }
                else if (strcmp(msg_pkt->getType(),"Ack")==0)
                {
                    EV << "\nAcknowledgement Received!";

                    Msgpacket* msg_new = new Msgpacket();
                    msg_new->setType("Data");
                    msg_new->setId(1);
                    msg_new->setSource_address(sourc);
                    msg_new->setDestination_address(dest);
                    send (msg_new, gOut);

                    counter--;
                    EV << "\nData Sent!";
                }
            }
        }
    }
}
