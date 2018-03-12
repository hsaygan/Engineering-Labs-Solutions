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

#include "physical.h"

Define_Module(Physical);

void Physical::initialize()
{
    inA =gate("inA");
    outA=gate("outA");
    inB =gate("inB");
    outB=gate("outB");
}

void Physical::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGate()==inA )
    {
        DL_PDU *pkt = check_and_cast<DL_PDU*> (msg);

        P_PDU *msg_new = new P_PDU("P_PDU");
        msg_new->encapsulate(pkt);

        send(msg_new,outB);
        EV << "Sending packet from physical to physical";
    }
    else if(msg->getArrivalGate()==inB)
    {
        P_PDU *pkt = check_and_cast<P_PDU*> (msg);

        DL_PDU *msg_new = check_and_cast<DL_PDU*> (pkt->decapsulate());

        send(msg_new,outA);
        EV << "Sending packet from physical to Datalink";
    }
}
