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
    inone =gate("inone");
    outone=gate("outone");
    intwo =gate("intwo");
    outtwo=gate("outtwo");
    id = par("id");
}

void Datalink::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->getArrivalGate()==inone )
    {
        A_PDU *pkt = check_and_cast<A_PDU*> (msg);
        DL_PDU *pkt2 = new DL_PDU("DL_PDU");
        pkt2->setSrc(pkt->getSrc()+1);
        pkt2->setDest(pkt->getDest()+1);
        pkt2->setType(0); // data -> '0' as it was sent by app layer !
        pkt2->encapsulate(pkt);
        send(pkt2,outtwo);
        EV << "Data sent from Data Link to Physical";
    }
    else if(msg->getArrivalGate()==intwo)
    {

        DL_PDU *pkt = check_and_cast<DL_PDU*> (msg);
        if(pkt->getDest()==2)
        {
           if(pkt->getType()==0) // Data packet received
           {
                A_PDU *pkt2 = check_and_cast<A_PDU*> (pkt->decapsulate());
                send(pkt2,outone);
                //  Sending ACK2 !
                DL_PDU *pkt3 = new DL_PDU("DL_PDU");
                pkt3->setSrc(pkt->getDest());
                pkt3->setDest(pkt->getSrc());
                pkt3->setType(1); // ACK -> '1'
                send(pkt3,outtwo);
                EV << "ACK sent from Data Link to Physical";
            }
            if(pkt->getType()==1) // ACK1 packet received
            {
               // Do Nothing...
                EV << "ACK Received by Data Link of Node 1";
            }
                }
        else if (pkt->getDest()==4)
        {
            if(pkt->getType()==0) // Data packet received
            {
                A_PDU *pkt2 = check_and_cast<A_PDU*> (pkt->decapsulate());
                send(pkt2,outone);
                //  Sending ACK1 !
                DL_PDU *pkt3 = new DL_PDU("DL_PDU");
                pkt3->setSrc(pkt->getDest());
                pkt3->setDest(pkt->getSrc());
                pkt3->setType(1); // ACK -> '1'
                send(pkt3,outtwo);
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
