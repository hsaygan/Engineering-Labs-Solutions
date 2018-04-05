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

#ifndef __LAB6_NODE_H_
#define __LAB6_NODE_H_

#include <omnetpp.h>
#include "bits/stdc++.h"
#include "R_PDU_m.h"
using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
  public:
    int id;
    int cnt;
    map<int,int> table[5];
    int mysrc;
    int dist[5];
    set<int> bag;
    int matrix[5][5];
    cGate* in1;
    cGate* in2;
    cGate* in3;
    cGate* out1;
    cGate* out2;
    cGate* out3;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void setMatrix(int row,int arr[]);
    void setPktMatrix(int row,R_PDU *pkt);
    void bellManFord();
    void arrSetter1(R_PDU *pkt1,R_PDU *pkt);
    void printMatrix();
    void arrSetter2(R_PDU *msg);

};

#endif
