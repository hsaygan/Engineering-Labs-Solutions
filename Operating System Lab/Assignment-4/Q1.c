#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

char buffer;
int flag = 0;

//Read function to read the characters from the read file and store into buffer
void read_function(void *read_file)
{
		printf("\nRead Function Initiated!");
    char ch; int i=0;
    FILE *read;
    read = (FILE *)read_file;
    printf("\n+ : Character is added to the buffer\n- : Character is moved from buffer to file :\n");

    while(ch != EOF)
		{
	  	if(flag == 0)
			{
					ch = fgetc(read);
	    		printf("+%c",ch);
	    		buffer = ch;
					flag = 1;
			}
			//printf("-");
    }
		printf("\n==== EOF ====");
		flag = 3;
}

//Write function to write the buffer characters to the write file
void write_function(void *write_file)
{
		printf("\nWrite Function Initiated!");
    FILE *write;
    write = (FILE *)write_file;
		while(flag != 3)
		{
			if(flag == 1)
			{
					fputc(buffer, write);
					printf("-%x", ch);
					flag = 0;
			}
		}
}


int main(int argc,char *argv[])
{
		FILE *read_file, *write_file;
		read_file = fopen(argv[1],"r");
		write_file = fopen(argv[2],"w");

		if (read_file == NULL || write_file == NULL)
		{
				printf("\nFiles Invalid!");
				exit(0);
		}

		pthread_t tid_read;
		pthread_t tid_write;

		pthread_create(&tid_read,NULL,read_function,(void *)read_file);
		pthread_create(&tid_write,NULL,write_function,(void *)write_file);

		pthread_join(tid_read,NULL);
		pthread_join(tid_write,NULL);
}
