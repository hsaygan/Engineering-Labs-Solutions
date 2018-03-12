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

network TwoNode
{
    @display("bgb=217,309");
    submodules:
        node1: Node {
            id = 1;
            @display("p=36.833332,160.59332");
        }

        node2: Node {
            id = 2;
            @display("p=167.22333,159.85666");
        }

    connections:
        node1.out --> node2.in;
        node2.out --> node1.in;
}
