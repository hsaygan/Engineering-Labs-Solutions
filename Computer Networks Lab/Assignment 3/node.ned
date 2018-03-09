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
    parameters:
        int id;
        int src;
        int dest;
        @display("bgb=188,259");
    gates:
        input in;
        output out;
    submodules:
        app: Application {
            @display("p=91,32");
            aid = id;
            count = 0;
        }
        data: Datalink {
            @display("p=91,119");
            did = id;
        }
        phy: Physical {
            @display("p=91,183");
            pid = id;
        }
    connections:
        app.to_dl --> data.from_al;
        data.to_pl --> phy.from_dl;
        phy.to_medium --> out;
        in --> phy.from_medium;
        phy.to_dl --> data.from_pl;
        data.to_al --> app.from_dl;
}
