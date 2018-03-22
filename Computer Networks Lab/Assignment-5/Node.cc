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

#include "Node.h"
#include <stdlib.h>
#include <msgpacket_m.h>
Define_Module(Node);

void Node::initialize()
{
    inA = gate("inA");
    inB = gate("inB");
    inC = gate("inC");

    outA = gate("outA");
    outB = gate("outB");
    outC = gate("outC");

    id = par("id");
    starting_node = par("starting_node");
    count = par("count");

    if(id==1)
    {
        node_map[2]=outA;
        node_map[3]=outB;
        node_map[4]=outC;
        node_map[5]=outB;
    }
    else if(id==2)
    {
        node_map[1]=outA;
        node_map[3]=outB;
        node_map[5]=outC;
        node_map[4]=outA;
    }
    else if(id==3)
    {
        node_map[1]=outA;
        node_map[2]=outB;
        node_map[5]=outC;
        node_map[4]=outA;
    }
    else if(id==4)
    {
        node_map[1]=outA;
        node_map[2]=outA;
        node_map[3]=outA;
        node_map[5]=outA;
    }
    else{
        node_map[2]=outA;
        node_map[3]=outB;
        node_map[1]=outB;
        node_map[4]=outB;
    }
    if(id==starting_node)
    {
        cMessage* event = new cMessage();
        scheduleAt(0,event);
    }
}

void Node::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
            int random;
            srand (time(NULL));
            while((random=rand()%5 + 1)==starting_node){}
            //random = 5;

            Msgpacket *new_msg=new Msgpacket();
            new_msg->setId(1);
            new_msg->setDestination_address(random);
            new_msg->setType(1);
            send(new_msg,node_map[random]);
            count--;
    }
    else
    {
        Msgpacket *m=check_and_cast<Msgpacket*>(msg);
        int destination = m->getDestination_address();
        if (destination==id)
        {
            if (m->getType()==1)
            {
                Msgpacket *ack=new Msgpacket();
                ack->setId(1);
                ack->setType(2);
                ack->setDestination_address(starting_node);
                send(ack, node_map[starting_node]);
            }
            else
            {
                int random;
                srand (time(NULL));
                while((random=rand()%5 + 1)==starting_node){}
                //random = 5;

                Msgpacket *new_msg=new Msgpacket();
                new_msg->setId(1);
                new_msg->setDestination_address(random);
                new_msg->setType(1);

                if(count!=0)
                {
                    send(new_msg,node_map[random]);
                    count--;
                }
             }
        }
        else
        {
            send(m,node_map[destination]);
        }
    }
}
