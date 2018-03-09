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
    // TODO - Generated method body
    inone =gate("inone");
    outone=gate("outone");
    intwo =gate("intwo");
    outtwo=gate("outtwo");
}

void Physical::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->getArrivalGate()==inone )
    {
        DL_PDU *pkt = check_and_cast<DL_PDU*> (msg);
        P_PDU *pkt2 = new P_PDU("P_PDU");
        pkt2->encapsulate(pkt);
        send(pkt2,outtwo);
        EV << "Sending packet from physical to physical";
    }
    else if(msg->getArrivalGate()==intwo)
    {
                P_PDU *pkt = check_and_cast<P_PDU*> (msg);
                DL_PDU *pkt2 = check_and_cast<DL_PDU*> (pkt->decapsulate());
                send(pkt2,outone);
                EV << "Sending packet from physical to Datalink";
    }
}
