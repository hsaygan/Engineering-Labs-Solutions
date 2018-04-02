#include<stdio.h>

struct process {
   int pid;
   int size;
   int location;
};

struct sector {
   int pid;
   int size;
   int location;
};

int i,j, mem_global[260];

struct sector s[10];

void allocateSector(int mem[],int p_id, int mem_size) {
	int s_no = -1, last=999; 
	for(i=0;i<mem_size;i++) {
		if(last!=mem[i]) {
			last = mem[i];
			s_no++;
			s[s_no].location = i;
			s[s_no].size = 1;
			s[s_no].pid = p_id;
		}
		else {
			s[s_no].size++;
		}
	}
}

void allocateMem(int mem[],int index, int p_size, int pid, int mem_size) {
	for(i=index;i<p_size;i++) {
		mem[i]=pid;
	}
	for(i=0;i<mem_size;i++) {
		mem_global[i] = mem[i];
	}
}

void main() {
	int totalMem;		

	scanf("%d",&totalMem);

	int mem[totalMem],
		req[10],
		reqAlloc[10],
		reqNo,
		tempAlloc,
		index = 0;

	for(i=0; i<totalMem; i++){
		mem[i] = -1;
	}

	scanf("%d",&reqNo);
	for(i=0; i<reqNo; i++){
		scanf("%d %d",&req[i], &reqAlloc[i]);
	}
	for(i=0; i<reqNo; i++){
		if(reqAlloc[i]!=0) {
			allocateMem(mem,index,reqAlloc[i],req[i], totalMem);
			allocateSector(mem,req[i],totalMem);
			index += reqAlloc[i];
		}
	}
	for (i=0; i<10;i++){
		printf("Sector %d -> size = %d, location = %d, pid = %d \n",i,s[i].size, s[i].location, s[i].pid);
	}
}
