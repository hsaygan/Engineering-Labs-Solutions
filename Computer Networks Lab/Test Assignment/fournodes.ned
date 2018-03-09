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

network Fournodes
{
    submodules:
        N1: Starting_node {
            id = 1;
            @display("p=58,150");
        }

        N2: Node {
            id = 2;
            @display("p=147,76");
        }

        N3: Node {
            id = 3;
            @display("p=263,76");
        }

        N4: Starting_node {
            id = 4;
            @display("p=349,150");
        }

    connections:
        N1.out --> N2.inA;
        N2.outA --> N1.in;
        N2.outB --> N3.inA;
        N3.outA --> N2.inB;
        N3.outB --> N4.in;
        N4.out --> N3.inB;
}
