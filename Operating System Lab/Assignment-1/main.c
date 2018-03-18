// QUESTION 1
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(void)
{
	struct dirent *de;
	char var[50];
	scanf("%s", var);
	DIR *dr = opendir(var);

	if (dr == NULL) 
	{
	printf("Could not open current directory" );
	return 0;
	}

	while ((de = readdir(dr)) != NULL)
	{
		printf("\n%s ", de->d_name);
		if ( de->d_type == 0x8)
		{
			printf("-- File");
		}
		else
		{
			printf("-- Directory");
		}
	}

	closedir(dr);    
	return 0;
}

// QUESTION 2
#include <stdio.h>
#include <string.h>

int main()
{
	char filename[20], *line;
	char delimiter; 
	int column;
	size_t len = 0;
        ssize_t read;

	printf("\nInput the following :\nFilename\nDelimiter\nColumn Number\n");
	scanf("%s %c %d", filename, &delimiter, &column); 
	printf("%s %c %d", filename, delimiter, column);
	
	//Test
	strcpy (filename, "randomfile.txt");
	delimiter = ',';
	column = 3;
	//

	FILE *fp;
	fp = fopen(filename, "r");

	while ((read = getline(&line, &len, fp)) != -1) 
	{
	        printf("\nLine : %s", line);

		char entity[50];
		int i=0, j=0, count=0;
		for (i=0; i<strlen(line); i++)
		{
			char c = line[i];
			if (c == delimiter)
			{
				count++;
			}
			else
			{
				if (count < column-1)
				{
					continue;
				}
				else if (count > column)
				{
					break;
				}
				else if (count >= column -1 && count < column)
				{
					entity[j] = c;
					j++;
				}
			}
		}
		printf("\nEntity : %s", entity);
		
	}
	fclose(fp);
}



// QUESTION 3
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // Fork returns process id
    // in parent process
    pid_t child_pid = fork();
 
    // Parent process 
    if (child_pid > 0)
        sleep(50);
 
    // Child process
    else       
        exit(0);
 
    return 0;
}

//Orphan Process
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
 
int main()
{
    //Child process      
    int pid = fork();
 
    if (pid > 0)
        printf("in parent process");
 
    //pid is 0 in child process
    //and negative if fork() fails
    else if (pid == 0)
    {
        sleep(30);
        printf("in child process");
    }
 
    return 0;
}
*/


