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

#include "datalink.h"
#include "string.h"
#include <omnetpp.h>

Define_Module(Datalink);

void Datalink::initialize()
{
    inA = gate("inA");
    inB = gate("inB");
    outA = gate("outA");
    outB = gate("outB");
    count = 0;
    retransmit = new cMessage();
}

void Datalink::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        if(msg == retransmit)
        {
            EV << "retransmitting";
            send(buffer, outB);
        }
    }
    else if(msg->getArrivalGate() == inA)
    {
        A_PDU* a = check_and_cast<A_PDU*>(msg);
        d = new DL_PDU();
        int id = a->getAid();
        id = (id+1)%2;
        d->setType("DATA");
        d->setDid(id);
        d->encapsulate(a);
        buffer = d->dup();
        R_pointer = (id+1) % 2;
        scheduleAt(simTime() + 10.0, retransmit);

        if(uniform(0,1) <= 0.3)
        {
            sendDelayed(d, simTime()+2.0,outB);
        }
        else
        {
            sendDelayed(d, simTime()+1.0,outB);
        }
    }
    else if(msg->getArrivalGate() == inB)
    {
        d = check_and_cast<DL_PDU*>(msg);
        if(strcmp(d->getType(),"DATA")== 0)
        {
            int id = d->getDid();
            id = (id+1)%2;
            DL_PDU* ack = new DL_PDU();
            ack->setType("ACK");
            ack->setDid(id);

            if(uniform(0,1) <= 0.4)
            {
                sendDelayed(d->decapsulate(), simTime()+2.0, outA);
                sendDelayed(ack, simTime()+2.0, outB);
            }
            else
            {
                sendDelayed(d->decapsulate(), simTime()+1.0, outA);
                sendDelayed(ack, simTime()+1.0, outB);
            }
        }
        else
        {
            if(R_pointer == d->getDid())
            {
                buffer = NULL;
                cancelEvent(retransmit);
            }
            else
            {
                EV << "this";
                delete msg;
            }
        }
    }
}
