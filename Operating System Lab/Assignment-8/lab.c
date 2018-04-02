#include <stdio.h>
#include <stdlib.h>
#define size 256
#include <string.h>

int rem = 256, mem[size], noOfProc, totalFree;
int blockSize[20], blockAddress[20], blockProc[20];

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void detectBlocks() {
	int blockNo = 999, count = -1, procSize = 1, i;
	for (i=0; i<size; i++) {
		if(mem[i]==blockNo) {
			procSize++;
			blockSize[count] = procSize;
		}
		else {
			procSize = 1;
			count++;
			blockNo = mem[i];
			blockAddress[count] = i;
			blockProc[count] = blockNo;
			blockSize[count] = procSize;
		}
	}
	noOfProc = count + 1;
	for(i=0; i<noOfProc; i++) {
		printf("Process: %d <==> Size: %d <==> Address: %d\n",blockProc[i], blockSize[i], blockAddress[i]);
	}
}

void compaction() {
	qsort(mem, size, sizeof(int), cmpfunc);
	detectBlocks();
}

void allocate(int pNo, int pSize) {
	detectBlocks();
	printf("Remaining Memory: %d\n",rem);
	int allPos=-1, minSize=257, i, flag = 0;
	printf("%d\n",noOfProc);
	for(i=0; i<noOfProc; i++) {
		if(blockSize[i] > pSize && blockProc[i] == -1) {
			if (blockSize[i] < minSize) {
				minSize = blockSize[i];
				allPos = i;
			}
		}
	}
	if(allPos != -1)
    {
		printf("Allocating P%d at Address %d\n", pNo, allPos);
		for(i = blockAddress[allPos]; i < blockAddress[allPos]+pSize; i++)
        {
			mem[i] = pNo;
		}
		rem = rem - pSize;
		printf("Remaining Memory: %d\n",rem);
	}
	else
    {
		if(rem > pSize)
        {
			printf("Doing Compaction \n");
				compaction();
			printf("Reallocating\n");
				//allocate(pNo, pSize);
		}
		else {
			printf("Not Enough Memory\n");
		}
	}
}

void deAllocate(int pNo)
{
	detectBlocks();
	int i,flag = 0;
	for(i=0; i<size; i++) {
		if(mem[i] == pNo) {
			if(flag == 0 && mem[i-1] == -1) flag = 1;
			mem[i] = -1;
		} wabba;
	}
	if(flag = 1) printf("\n Coalescing Memory\n");
}

void main()
{
	int i,j,req;
	for(i = 0; i < size ; mem[i++] = -1);
	printf("\n\nTotal Memory Size: 256\n");
	printf("Enter the number of requests: ");
	scanf("%d",&req);
	int reqArray[req], sizeArray[req];
	for (i=0; i<req; i++)
    {
		scanf("%d %d",&reqArray[i],&sizeArray[req]);
	}
	for (i=0; i<req; i++)
    {
		if(sizeArray[i] == 0)
        {
			deAllocate(reqArray[i]);
		}
		else {
			allocate(reqArray[i], sizeArray[i]);
		}
	}
}
