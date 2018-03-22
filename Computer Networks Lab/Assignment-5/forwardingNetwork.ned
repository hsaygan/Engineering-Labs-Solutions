//
// This program is free software: you can redistribute it aNode4/or modify
// it uNode4er the terms of the GNU Lesser GeNode5ral Public License as published by
// the Free Software FouNode4ation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNode5SS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser GeNode5ral Public License for more details.
// 
// You should have received a copy of the GNU Lesser GeNode5ral Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

network ForwardingNetwork
{	
    submodules:
        Node1: Node 
        {
            id = 1;
            @display("p=69,43");
        }
        Node2: Node 
        {
            id = 2;
            @display("p=358,43");
        }
        Node3: Node 
        {
            id = 3;
            @display("p=212,214");
        }
        Node4: Node 
        {
            id = 4;
            @display("p=46,238");
        }
        Node5: Node 
        {
            id = 5;
            @display("p=397,214");
        }

    connections allowunconnected:
        Node1.inA <-- Node2.outA;
        Node2.inA <-- Node1.outA;
        Node1.inB <-- Node3.outA;
        Node3.inA <-- Node1.outB;
        Node1.inC <-- Node4.outA;
        Node4.inA <-- Node1.outC;
        Node3.inB <-- Node2.outB;
        Node2.inB <-- Node3.outB;
        Node2.inC <-- Node5.outA;
        Node5.inA <-- Node2.outC;
        Node3.inC <-- Node5.outB;
        Node5.inB <-- Node3.outC;
}
