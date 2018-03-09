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
#include "string.h"

Define_Module(Physical);

void Physical::initialize()
{
    from_dl = gate("from_dl");
    from_medium = gate("from_medium");
    to_dl = gate("to_dl");
    to_medium = gate("to_medium");
    // TODO - Generated method body
}

void Physical::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGate() == from_dl){
        DL_PDU* d = check_and_cast<DL_PDU*>(msg);
        P_PDU* p = new P_PDU();
        p->encapsulate(d);
        if(uniform(0,1) < 0.1){
            EV << "message deleted";
            delete p;
        } else {
            send(p, to_medium);
        }
    } else if(msg->getArrivalGate() == from_medium){
        P_PDU* p = check_and_cast<P_PDU*>(msg);
        if(uniform(0,1) < 0.15){
            EV << "message deleted";
            delete p;
        } else {
            send(p->decapsulate(), to_dl);
        }
    }
    // TODO - Generated method body
}
