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

Define_Module(Datalink);

void Datalink::initialize()
{
    // TODO - Generated method body
    inA =gate("inA");
    outA=gate("outA");
    inB =gate("inB");
    outB=gate("outB");
    id = par("id");
}

void Datalink::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->getArrivalGate()==inA)
    {
        A_PDU *pkt = check_and_cast<A_PDU*> (msg);

        DL_PDU *msg_new = new DL_PDU("DL_PDU");
        msg_new->setSource_address(pkt->getSource_address()+1);
        msg_new->setDestination_address(pkt->getDestination_address()+1);
        msg_new->setType(0);                   // Data: 0
        msg_new->encapsulate(pkt);

        send(msg_new,outB);
        EV << "Data sent from Data Link to Physical";
    }
    else if(msg->getArrivalGate()==inB)
    {
        DL_PDU *pkt = check_and_cast<DL_PDU*> (msg);

        if(pkt->getDestination_address()==2)
        {
            if(pkt->getType()==0) // Data packet received
            {
                A_PDU *pkt2 = check_and_cast<A_PDU*> (pkt->decapsulate());
                send(pkt2,outA);

                //Sending ACK2
                DL_PDU *msg_new = new DL_PDU("DL_PDU");
                msg_new->setSource_address(pkt->getDestination_address());
                msg_new->setDestination_address(pkt->getSource_address());
                msg_new->setType(1);                                        // ACK -> '1'

                send(msg_new,outB);
                EV << "ACK sent from Data Link to Physical";
            }
            else if(pkt->getType()==1) // ACK1 packet received
            {
               //Do Nothing
                EV << "ACK Received by Data Link of Node 1";
            }
        }
        else if (pkt->getDestination_address()==4)
        {
            if(pkt->getType()==0) // Data packet received
            {
                A_PDU *pkt2 = check_and_cast<A_PDU*> (pkt->decapsulate());
                send(pkt2,outA);

                //  Sending ACK1 !
                DL_PDU *msg_new = new DL_PDU("DL_PDU");
                msg_new->setSource_address(pkt->getDestination_address());
                msg_new->setDestination_address(pkt->getSource_address());
                msg_new->setType(1); // ACK -> '1'

                send(msg_new,outB);
                EV << "ACK sent from Data Link to Physical";
            }
            if(pkt->getType()==1) // ACK2 packet received
            {
               // Do Nothing...
                EV << "ACK Received by Data Link of Node 2";
            }
        }

    }
}
