#include <stdio.h>
void main() {
	int i, j, nof, nopr, time = 0, loc, eflag, fflag, maxT, minR, pf, pfc=0;
	printf("\n\n================================\n");
	scanf("%d %d", &nof, &nopr);
	printf("\n");
	int w[nopr],x[nof],t[nof],r[nof];
	for(i=0; i<nopr; i++) {
		scanf("%d",&w[i]);
	}
	printf("\n+----+----+----+----+----+\n");
	for(i=0; i<nof; i++) {
		x[i] = -1;
		t[i] = 0;
		r[i] = 0;
	}	
	for(i=0; i<nopr; i++) {
		pf = 0;
		eflag = 0;
		fflag = 0;
		maxT = 0;
		minR = 999; 
		time++;
		for(j=0; j<nof; j++){
			if(x[j] == -1) {
				loc = j;
				eflag = 1;
				break;
			}
		}
		for(j=0; j<nof; j++){
			if(x[j] == w[i]) {
				loc = j;
				fflag = 1;
				break;
			}
		}
		if (eflag!=1) {
			if(fflag!=1) {
				pf = 1;
				pfc++;
				for(j=0; j<nof; j++){
					if (minR > r[j]) {
						loc = j;
						minR = r[j];
					}
					else if(minR == r[j]) {
						if(maxT < t[j]) {
							loc = j;
							maxT = t[j];
						}
					}
				}
				x[loc] = w[i];
				t[loc] = time;
				r[loc] = 1;				
			}
			else {
				t[loc] = time;
				r[loc]++;
			}
							
		}
		else {
			x[loc] = w[i];
			t[loc] = time;
			r[loc] = 1;
		}
		//Printing
		printf("|");
		for(j=0; j<nof; j++){
			if(x[j]/10==0 && x[j]!=-1){
				printf("  %d |",x[j]);
			} 
			else {
				printf(" %d |",x[j]);
			} 
		}			
		if (pf == 1) printf("\t F");
		printf("\n");
	}		
	printf("+----+----+----+----+----+\n");	
	printf("\nNo. Of Page Faults: %d",pfc);
	printf("\nMiss Rate: %f\n\n",(double)pfc/nopr);		
}


/*Write a program to simulate hybrid Least Recently Used (LRU) and Least Frequently Used (LFU)
virtual memory page replacement algorithm. The LRU algorithm replaces the least recently used
items first so you need to keep track of which page is used when. The idea of LFU is very simple
Counts how often an item is needed. Those that are used least often are replaced first. The idea
behind this hybrid of LRU and LFU is to build a tradeoff of both. If there is a situation when there
is a completion for page to be replaced is between most frequently used pages or most recently
used pages the hybrid algorithm will replace any of the recently used pages (according to LRU) to
keep the frequently use page in frame.
Specifications of the page replacement simulator is as follows:
The input to this program are the total number of physical memory frames (maximum 100), (b) a
sequence of page references (integers in the range 0 to 99 separated by space in single line) e.g.:
5
51 7 34 0 8 51 34 7 8 45 50 34 21 8 0 45 34 51 35
The program will first read all the memory references and store them in a local array or suitable
data structure. Then, it will play back these references one by one and print out for each reference
the current allocation state of physical memory frames in the following format:
34: [51| 7|34| | ]
This line means that after using page 34, frames 0, 1 and 2 are occupied by pages 51, 7 and 34,
and frames 3 and 4 are empty. Frames must start with open square bracket [, end with closed square
bracket ] and be separated with vertical bar |. One-digit page numbers should have an extra space
to the left so that frames are always 2 characters wide. Each page fault should be signaled by an F
character two spaces to the right of the closed bracket, for example:
45: [51| 7|34| 45| 8] F
After processing all the memory references, the program should finally print the total number of
page faults and the miss rate (total number of page faults divided by number of references).


| 51 |  7 | 34 |    |    |									51 - 1, 7 - 2, 34 - 3 
| 51 |  7 | 34 |  0 |    |									51 - 1, 7 - 2, 34 - 3, 0 - 4
| 51 |  7 | 34 |  0 |  8 |									51 - 1, 7 - 2, 34 - 3, 0 - 4, 8 - 5
| 51 |  7 | 34 |  0 |  8 |  	51x2						51 - 6, 7 - 2, 34 - 3, 0 - 4, 8 - 5
| 51 |  7 | 34 |  0 |  8 |  	51x2, 34x2					51 - 6, 7 - 2, 34 - 7, 0 - 4, 8 - 5
| 51 |  7 | 34 |  0 |  8 |  	51x2, 34x2, 7x2				51 - 6, 7 - 8, 34 - 7, 0 - 4, 8 - 5
| 51 |  7 | 34 |  0 |  8 |  	51x2, 34x2, 7x2, 8x2		51 - 6, 7 - 8, 34 - 7, 0 - 4, 8 - 9
| 51 |  7 | 34 | 45 |  8 |  	51x2, 34x2, 7x2, 8x2		51 - 6, 7 - 8, 34 - 7, 8 - 9, 45 - 10		F1
| 51 |  7 | 34 | 50 |  8 |  	51x2, 34x2, 7x2, 8x2		51 - 6, 7 - 8, 34 - 7, 8 - 9, 50 - 11		F2
| 51 |  7 | 34 | 50 |  8 |  	51x2, 34x3, 7x2, 8x2		51 - 6, 7 - 8, 34 - 12, 8 - 9, 50 - 11		F2
| 51 |  7 | 34 | 21 |  8 |  	51x2, 34x3, 7x2, 8x2		51 - 6, 7 - 8, 34 - 12, 8 - 9, 21 - 13		F3
| 51 |  7 | 34 | 21 |  8 |  	51x2, 34x3, 7x2, 8x3		51 - 6, 7 - 8, 34 - 12, 8 - 14, 21 - 13		F3
| 51 |  7 | 34 |  0 |  8 |  	51x2, 34x3, 7x2, 8x3		51 - 6, 7 - 8, 34 - 12, 8 - 14, 0 - 15		F4
| 51 |  7 | 34 | 45 |  8 |  	51x2, 34x3, 7x2, 8x3		51 - 6, 7 - 8, 34 - 12, 8 - 14, 45 - 16		F5
| 51 |  7 | 34 | 45 |  8 |  	51x2, 34x4, 7x2, 8x3		51 - 6, 7 - 8, 34 - 17, 8 - 14, 45 - 16		F5
| 51 |  7 | 34 | 45 |  8 |  	51x3, 34x4, 7x2, 8x3		51 - 18, 7 - 8, 34 - 17, 8 - 14, 45 - 16	F5
| 51 |  7 | 34 | 35 |  8 |  	51x3, 34x4, 7x2, 8x3		51 - 18, 7 - 8, 34 - 17, 8 - 14, 35 - 19	F6






*/


