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

#ifndef __LAB5_NODE_H_
#define __LAB5_NODE_H_
#include <bits/stdc++.h>
#include <omnetpp.h>

using namespace std;
using namespace omnetpp;

class Node : public cSimpleModule
{
    protected:
        cGate *inA,*inB, *inC;
        cGate *outA,*outB,*outC;
        int id, starting_node, count;
        std ::map<int,cGate*> node_map;

        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif
