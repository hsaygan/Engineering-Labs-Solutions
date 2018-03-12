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

#include "node.h"
#include "msgpacket_m.h"

Define_Module(Node);

void Node::initialize()
{
    id = par("id");
    gIn = gate("in");
    gOut = gate("out");
    count = 0;

    if(id == 1)
    {
        cMessage* msg = new cMessage();
        scheduleAt(0, msg);
    }
}

void Node::handleMessage(cMessage *msg)
{
    //Self Message
    if (msg->isSelfMessage())
    {
        Msgpacket* packet = new Msgpacket("Data");
        packet->setId(count);
        packet->setType(1);
        packet->setSource_address(1);
        packet->setDestination_address(2);

        count++;
        send(packet,gOut);
    }
    //Inter Node Message
    else if (count < 10)
    {
        Msgpacket* new_packet = check_and_cast<Msgpacket*>(msg);    //Casting Message to custom packet type

        //Received Message is Data
        if (new_packet->getType() == 1)
        {
            Msgpacket* packet = new Msgpacket("Ack");
            packet->setId(new_packet->getId());
            packet->setType(0);
            packet->setSource_address(2);
            packet->setDestination_address(1);

            send(packet, gOut);
        }
        //Received Message is Ack
        else
        {
            Msgpacket* packet = new Msgpacket("Data");
            packet->setId(count);
            packet->setType(1);
            packet->setSource_address(1);
            packet->setDestination_address(2);

            count++;
            send(packet, gOut);
        }
    }
}
