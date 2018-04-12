#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
void reverse(char *s)
{
   int length, c;
   char *begin, *end, temp;
 
   length = strlen(s);
   begin  = s;
   end    = s;
 
   for (c = 0; c < length - 1; c++)
      end++;
 
   for (c = 0; c < length/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
}


void convert_to_string(char *res,int num)
{
  int i = 0, length;
  length = strlen(res);

  while(num > 0)
  {
    res[i++] = (num%10) + '0';
    num = num/10;
  }
  res[i] = '\0';
  reverse(res);
}

char* get_result(char *buf)
{
  char num1[100], num2[100], operator;
  int i = 0, k=0, ans;

  while(buf[i]!=' ' && buf[i]!='\n' && buf[i]!='\0')
    num1[k++] = buf[i++];
  num1[k]='\0';
  k = 0; i++;

  while(buf[i]!=' ' && buf[i]!='\n' && buf[i]!='\0')
    operator = buf[i++];
  
  i++;

  while(buf[i]!=' ' && buf[i]!='\n' && buf[i]!='\0')
    num2[k++] = buf[i++];
  num2[k]='\0';
 
  if (operator == '+')
  {
	ans = atoi(num1) + atoi(num2);
  }
  else if (operator == '-')
  {
	ans = atoi(num1) - atoi(num2);
  }
  else if (operator == 'x')
  {
	ans = atoi(num1) * atoi(num2);
  }
  else if (operator == '/')
  {
	ans = atoi(num1) / atoi(num2);
  }
	
  char *res = malloc(sizeof(char) * 1024);
  convert_to_string(res,ans);

  return res;
}

int main(int argc, char const *argv[])
{
  int status;
  struct addrinfo hints;
  struct addrinfo *result;
  memset(&hints , 0, sizeof( struct addrinfo ));

  //TCP Stream Sockets
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, "1026", &hints, &result)) != 0)
  {
    fprintf(stderr, "getaddrinfo Error: %s\n", gai_strerror(status));
    exit(1);
  }
  printf("\n\t| Address Received |\n");
  int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  bind(sockfd, result->ai_addr, result->ai_addrlen);
  listen(sockfd,1);
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  addr_size = sizeof(their_addr);
  while(1)
  {
    int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    printf("\nConnection established!\n");
    char *buf = "\0";
    buf = malloc(1024*sizeof(char));
    int numOfBytesReceived = recv(new_fd,(void *)(buf),1024,0);
    printf("\n\tMessage Received!");

    char *res = get_result(buf);
    printf("\nResult Message: %s",res);
    printf("\n\tResult Sent!\n\nWaiting for Request...\n");
    
    send(new_fd,res,strlen(res)*sizeof(char),0);
  }
  close(sockfd);
  return 0;
}
