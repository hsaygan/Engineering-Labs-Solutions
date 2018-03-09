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

#include "application.h"

Define_Module(Application);

void Application::initialize()
{
    gIn =gate("in");
    gOut=gate("out");
    id = par("id");
    count = 0;

    if(id==1)
    {
        cMessage *msg = new cMessage();
        scheduleAt(0,msg);
        EV << "\nSelf message generated at Node 1";
    }
}

void Application::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
            A_PDU *new_msg = new A_PDU("A_PDU");
            new_msg->setData("HelloWorld!");
            new_msg->setSource_address(1);
            new_msg->setDestination_address(3);
            new_msg->setType(0);                //Data
            send(new_msg, gOut);

            count++;
            EV << "Data1 send from APP to Data Link";
    }
    else
    {
        A_PDU *new_msg = check_and_cast<A_PDU*> (msg);

        if(new_msg->getDestination_address()==1)
        {
            if(new_msg->getType()==1)
            {
                new_msg->setType(0);            //Data
                new_msg->setSource_address(1);
                new_msg->setDestination_address(3);

                if(count<10)
                {
                    send(new_msg,outG);

                    count++;
                    EV << "\nACK Received by APP_LAYER of Node1 and data packet sent from APP to Data Link!";
                }
                EV << "ACK Received by APP of Node1 !";
            }

        }
        else if(new_msg->getDestination_address()==3)
        {
            if(new_msg->getType()==0)//data packet received
            {
                new_msg->setType(1);            //Ack
                new_msg->setSource_address(3);
                new_msg->setDestination_address(1);
                send(pkt,outG);

                EV << "Data Packet Received by APP  and  Sending ACK From Node-2 APP !";
            }
        }
    }
}
