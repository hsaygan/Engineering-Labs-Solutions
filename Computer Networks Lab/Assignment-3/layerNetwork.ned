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

network LayerNetwork
{
    @display("bgb=450,97");
    submodules:
        node1: Node {
            id = 1;
            @display("p=109,30");
        }
        node2: Node {
            id = 2;
            @display("p=327,30");
        }
    connections:
        node1.out --> {  delay = 1ms; } --> node2.in;
        node2.out --> {  delay = 1ms; } --> node1.in;
}
