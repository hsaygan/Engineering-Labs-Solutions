#include<stdio.h> 
#include <stdlib.h>
#include <time.h>
#define MAX 10

int index_counter = 0;

//Bubble Sort
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int at[], int bt[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
    {
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

//RR Process Management
void *RR_process_management(int n_process, int time_quantum, int *at, int *bt, int *final_schedule)
{	
	//Display Process Schedule Iteration
	printf("\nProcess Schedules : \n");
  	int counter=0, burst=n_process;
	for (counter=0; counter<100; counter+=quantum)
	{
		//printf("\nCounter : %d", counter);
		//int flag = 0;
		for (count=0; count<n_process; count++)	//Count is the process number
		{
			//printf("\n\tProcess : %d", count+1);
			if (at[count] <= counter && bt[count] > 0)
			{
				final_schedule[index_counter++] = count;
				printf("| P[%d] ", count+1);
				bt[count]--;
				flag++;
				//printf("\nCounter : %d", counter);
			}
			//printf("\n\tProcess Ended!");
		}
		/*if (flag)
		{
			//counter+=flag-1;
		}*/
		//printf(" A ");
		burst=n_process;
		for (count=0; count<n_process; count++)
		{
			if (bt[count] < 0)
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
}

//Display Process Specs
void display_process_specs(int n_process, int *at, int *bt)
{
	bubbleSort(at, bt, n_process);
	printf("\n\n|Process Number\t|Arrival Time|\tBurst Time|\n"); 
	for (count=0; count<n_process; count++)
	{
		printf("\n\t%d\t\t%d\t\t%d", count+1, at[count], bt[count]);
	}
}

//Main Function
int main() 
{
	pthread_t tid[2];
    	pthread_join(tid, NULL);
    	printf("\nAfter Thread");	
	
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
		//bt[count] = at[count] + rand() % (MAX - at[count]);
		bt[count] = rand() % MAX;
	}

	printf("\nEnter Time Quantum:\t"); 
	scanf("%d",&time_quantum); 
	
	//Display Process Specs
	display_process_specs(n_process, at, bt)

	/*printf("\n\n|Process Number\t|Arrival Time|\tBurst Time|\n"); 
	for (count=0; count<n; count ++)
	{
		printf("\n\t%d\t\t%d\t\t%d", count+1, at[count], bt[count]);
		rt[count]=bt[count]; 
		burst_time[count] = bt[count]/time_quantum;
	}*/
	
	int final_schedule[100];
	
	//Odd and Even Distribution
	if (n%2 == 0)
	{
		int first_at[n/2], first_bt[n/2];'
		int second_at[n-(n/2)], second_bt[n-(n/2)];
	
		int i,j;
		for (count=0. i=0, j=0; count<n; count++)
		{
			if ((count+1)%2 == 0)
			{
				second_at[j] = at[count];
				second_bt[j++] = bt[count];
			}
			else
			{
				first_at[i] = at[count];
				first_bt[i++] = bt[count];
			}
		}
		pthread_create(&tid[0], NULL, RR_process_management(n_process, time_quantum, first_at, first_bt, final_schedule), NULL);
		pthread_create(&tid[1], NULL, RR_process_management(n_process, time_quantum, second_at, second_bt, final_schedule), NULL);
	}
	else
	{
		int first_at[(n+1)/2], first_bt[(n+1)/2];
		int second_at[n-(n+1/2)], second_bt[n-(n+1/2)];

		int i,j;
		for (count=0. i=0, j=0; count<n; count++)
		{
			if ((count+1)%2 == 0)
			{
				second_at[j] = at[count];
				second_bt[j++] = bt[count];
			}
			else
			{
				first_at[i] = at[count];
				first_bt[i++] = bt[count];
			}
		}
		pthread_create(&tid[0], NULL, RR_process_management(n_process, time_quantum, first_at, first_bt, final_schedule), NULL);
		pthread_create(&tid[1], NULL, RR_process_management(n_process, time_quantum, second_at, second_bt, final_schedule), NULL);
		
	}
		
	

	return 0; 
}
