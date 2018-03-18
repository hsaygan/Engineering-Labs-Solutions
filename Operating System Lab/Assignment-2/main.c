#include<stdio.h> 
#include <stdlib.h>
#include <time.h>
#define MAX 10

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(int at[], int bt[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
    {
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
       {
           if (at[j] > at[j+1])
           {
              swap(&at[j], &at[j+1]);
  	      swap(&bt[j], &bt[j+1]);
	   }
       }  
    }
}

int main() 
{ 
	//Declaration
	int count = 0 ,j,n,time_now,remain,flag=0,time_quantum; 
	int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10], burst_time[10]; 

	//Input
	printf("Enter Total Process:\t "); 
	scanf("%d",&n); 
	remain=n; 

	//Random Process Allotment
	srand(time(NULL));
	for(count=0;count<n;count++) 
	{ 
		at[count] = rand() % MAX;
		bt[count] = at[count] + rand() % (MAX - at[count]);
	}

	printf("\nEnter Time Quantum:\t"); 
	scanf("%d",&time_quantum); 
	
	//Display Process Specs
	bubbleSort(at, bt, n);
	printf("\n\n|Process Number\t|Arrival Time|\tBurst Time|\n"); 
	for (count=0; count<n; count ++)
	{
		printf("\n\t%d\t\t%d\t\t%d", count+1, at[count], bt[count]);
		rt[count]=bt[count]; 
		burst_time[count] = bt[count]/time_quantum;
	}

	//Display Process Schedule Iteration
	printf("\nProcess Schedules : \n");
  	int counter=0, burst=n;
	for (counter=0; counter<100; counter++)
	{
		//printf("\nCounter : %d", counter);
		//int flag = 0;
		for (count=0; count<n; count++)	//Count is the process number
		{
			//printf("\n\tProcess : %d", count+1);
			if (at[count] <= counter && burst_time[count] > 0)
			{
				printf("| P[%d] ", count+1);
				burst_time[count]--;
				flag++;
				//printf("\nCounter : %d", counter);
			}
			//printf("\n\tProcess Ended!");
		}
		//if (flag)
		//{
			//counter+=flag-1;
		//}
		//printf(" A ");
		burst=n;
		for (count=0; count<n; count++)
		{
			if (burst_time[count] < 0)
			{
				burst--;
			}
		}
		//printf(" B ");
		if (burst < 0)
		{
			break;
		}
		//printf("\nCounter Ended!");
	}

	/*
	printf("\n\n|Process\t|Turnaround Time|\tWaiting Time|\n\n"); 
	for(time_now=0,count=0; remain!=0;) 
	{ 
		if (rt[count]<=time_quantum && rt[count]>0) 
		{ 
			time_now+=rt[count]; 
			rt[count]=0; 
			flag=1; 
		} 
		else if (rt[count]>0) 
		{ 
			rt[count]-=time_quantum; 
			time_now+=time_quantum; 
		} 

		if(rt[count]==0 && flag==1) 
		{ 
			remain--; 
			printf("\tP[%d]\t|\t%d\t|\t%d\n",count+1,time_now-at[count],time_now-at[count]-bt[count]); 
			wait_time+=time_now-at[count]-bt[count]; 
			turnaround_time+=time_now-at[count]; 
			flag=0; 
		} 

		if (count==n-1) 
		count=0; 
		else if(at[count+1]<=time_now) 
			count++; 
		else 
		count=0; 
	} 

	printf("\nAverage Waiting Time= %f",wait_time*1.0/n); 
	printf("\nAvg Turnaround Time = %f",turnaround_time*1.0/n);

	//for every process: completion time, turnaround time, waiting time, response time
	//Combined: averages for all above*/

	return 0; 
}
