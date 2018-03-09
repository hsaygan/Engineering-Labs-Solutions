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

module Node
{
    @display("bgb=404,181");
    gates:
        input in;
        output out;

    submodules:
        Application: Application {
            @display("p=53,61");
        }
        Datalink: Datalink {
            @display("p=185,61");
        }
        Physical: Physical {
            @display("p=336,41");
        }
    connections:


        Application.out --> Datalink.inone;
        Datalink.outone --> Application.in;

        Datalink.outtwo --> Physical.inone;
        Physical.outone --> Datalink.intwo;

        Physical.outtwo --> out;
        in --> Physical.intwo;
}
