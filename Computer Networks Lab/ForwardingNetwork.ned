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

network ForwardingNetwork
{
    submodules:
        A: Node {
            nid = 0;
            @display("p=102,48");
        }
        B: Node {
            nid = 1;
            @display("p=468,42");
        }
        C: Node {
            nid = 2;
            @display("p=250,118");
        }
        D: Node {
            nid = 3;
            @display("p=102,204");
        }
        E: Node {
            nid = 4;
            @display("p=476,204");
        }
    connections allowunconnected:
         A.in1<--B.out1;
         A.in2<--C.out1;
         A.in3<--D.out1;
         B.in1<--A.out1;
         B.in2<--C.out2;
         B.in3<--E.out1;
         C.in1<--A.out2;
         C.in2<--B.out2;
         C.in3<--E.out2;
         D.in1<--A.out3;
         E.in1<--B.out3;
         E.in2<--C.out3;
            
}