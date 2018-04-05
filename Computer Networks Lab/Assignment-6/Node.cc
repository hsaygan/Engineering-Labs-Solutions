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

#include "Node.h"

Define_Module(Node);
void Node::setMatrix(int row,int arr[])
{
    for (int i = 0; i < 5; ++i)
    {
        matrix[row][i] = arr[i];
    }
}
void Node::setPktMatrix(int row,R_PDU *pkt)
{
    for (int i = 0; i < 5; ++i)
    {
        matrix[row][i] = min(pkt->getDist(i),matrix[row][i]);
        matrix[i][row] = min(pkt->getDist(i),matrix[i][row]);
    }
}
void Node::initialize()
{
    id = par("nid");
    mysrc = par("mySrc");
    cnt = par("cnt");
    in1 = gate("in1");
    in2 = gate("in2");
    in3 = gate("in3");
    out1 = gate("out1");
    out2 = gate("out2");
    out3 = gate("out3");
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
        {
            if(i == j) matrix[i][j] = 0;
            else
                matrix[i][j] = 1000;
        }
    if(id==0)//A
    {
        table[id].insert(make_pair(1,5));
        table[id].insert(make_pair(2,2));
        table[id].insert(make_pair(3,3));
        dist[0] = 0;
        dist[1] = 5;
        dist[2] = 2;
        dist[3] = 3;
        dist[4] = 1000;
        setMatrix(0,dist);
    }
    if(id==1) //B
    {
        table[id].insert(make_pair(0,5));
        table[id].insert(make_pair(2,4));
        table[id].insert(make_pair(4,3));
        // dist = {5,0,4,1000,3};
        dist[0] = 5;
        dist[1] = 0;
        dist[2] = 4;
        dist[3] = 1000;
        dist[4] = 3;
        setMatrix(1,dist);
    }
    if(id==2) //C
    {
        table[id].insert(make_pair(0,2));
        table[id].insert(make_pair(1,4));
        table[id].insert(make_pair(4,4));
        // dist = {2,4,0,1000,4};
        dist[0] = 2;
        dist[1] = 4;
        dist[2] = 0;
        dist[3] = 1000;
        dist[4] = 4;
        setMatrix(2,dist);
    }
    if(id==3) //D
    {
        table[id].insert(make_pair(0,3));
        // dist = {3,1000,1000,0,1000};
        dist[0] = 3;
        dist[1] = 1000;
        dist[2] = 1000;
        dist[3] = 0;
        dist[4] = 1000;
        setMatrix(3,dist);
    }
    if(id==4) //E
    {
        table[id].insert(make_pair(1,3));
        table[id].insert(make_pair(2,4));
        // dist = {1000,3,4,1000,0};
        dist[0] = 1000;
        dist[1] = 3;
        dist[2] = 4;
        dist[3] = 1000;
        dist[4] = 0;
        setMatrix(4,dist);
    }
    if(id == 2)
    {
        cMessage *msg = new R_PDU();
        scheduleAt(0,msg);
    }

}
void Node::bellManFord()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if(i == j) continue;
            for (int k = 0; k < 5; ++k)
            {
                if(matrix[i][j] > matrix[i][k] + matrix[k][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
}
void arrSetter(R_PDU *msg,int arr[])
{
    for(int i =0 ;i<5;i++)
        msg->setDist(i,arr[i]);
}
void Node::arrSetter2(R_PDU *msg)
{
    for(int i =0 ;i<5;i++)
        msg->setDist(i,matrix[id][i]);
}

void Node::arrSetter1(R_PDU *pkt1,R_PDU *pkt)
{
    for(int i =0 ;i<5;i++)
        pkt1->setDist(i,pkt->getDist(i));
}
void Node::printMatrix()
{
    EV << id << endl;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
            EV << matrix[i][j] << " " ;
        EV << endl;
    }
}
void Node::handleMessage(cMessage *msg)
{
  bag.insert(id);
//  printMatrix();
  if(msg->isSelfMessage())
  {
    R_PDU *pkt = new R_PDU();
    pkt->setSrc(id);
    arrSetter(pkt,dist);
    cnt--;
    R_PDU *pkt1 = new R_PDU();
    pkt1->setSrc(id);
    arrSetter(pkt1,dist);
    R_PDU *pkt2 = new R_PDU();
    pkt2->setSrc(id);
    arrSetter(pkt2,dist);
    send(pkt,out1);
    send(pkt1,out2);
    send(pkt2,out3);
}
else
{
    R_PDU *pkt = check_and_cast<R_PDU *>(msg);

    if(pkt->getSrc()!=id)
    {
       setPktMatrix(pkt->getSrc(),pkt);
       if(bag.find(pkt->getSrc()) == bag.end())
       {
           bag.insert(pkt->getSrc());
           setPktMatrix(pkt->getSrc(),pkt);
           bellManFord();
           R_PDU *pkt = new R_PDU();
           pkt->setSrc(id);
           arrSetter2(pkt);
           cnt--;
           R_PDU *pkt1 = new R_PDU();
           pkt1->setSrc(id);
           arrSetter2(pkt1);
           R_PDU *pkt2 = new R_PDU();
           pkt2->setSrc(id);
           arrSetter2(pkt2);
           send(pkt,out1);
           if(id !=3)
              send(pkt1,out2);
          if(id!=3 && id!=4)
              send(pkt2,out3);
      }
      bellManFord();
      printMatrix();
  }
}
}
