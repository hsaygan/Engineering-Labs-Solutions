//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more det ails.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
#include <string.h>
#include <omnetpp.h>
#include "msgpacket_m.h"
#include "node.h"

Define_Module(Node);

void Node::initialize()
{
    gInA = gate("inA");
    gInB = gate("inB");
    gOutA = gate("outA");
    gOutB = gate("outB");

    address = par("id");
}

void Node::handleMessage(cMessage *msg)
{
    //Inter-Message Handling
    Msgpacket* msg_pkt = check_and_cast<Msgpacket *>(msg);

    //If Destination Address > Current NodeID
    if(msg_pkt->getDestination_address() > address)
    {
        send (msg_pkt, gOutB);
    }

    //If Destination Address < Current NodeID
    if(msg_pkt->getDestination_address() < address)
    {
        send (msg_pkt, gOutA);
    }

    //If Destination Address = Current NodeID
    if(msg_pkt->getDestination_address() == address)
    {
        if (strcmp(msg_pkt->getType(),"Data")==0)
        {
            EV << "\nData Received!";

            Msgpacket* msg_new = new Msgpacket();
            msg_new->setType("Ack");
            msg_new->setId(2);
            msg_new->setSource_address(address);
            msg_new->setDestination_address(msg_pkt->getSource_address());

            if (msg_pkt->getSource_address() > address)
            {
                send (msg_new, gOutB);
            }
            else if (msg_pkt->getSource_address() < address)
            {
                send (msg_new, gOutA);
            }

            EV << "\nAcknowledgement Sent!";
        }
        else if (strcmp(msg_pkt->getType(),"Ack")==0)
        {
            EV << "\nAcknowledgement Received!";
            //End
        }
    }

}
