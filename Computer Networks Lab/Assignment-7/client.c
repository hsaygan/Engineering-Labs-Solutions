#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
  if(argc < 3)
  {
    printf("Please enter required number of operands\n");
    exit(0);
  }
  int status;
  struct addrinfo hints;
  struct addrinfo *result;
  memset(&hints , 0, sizeof( struct addrinfo ));
  
  //TEC Stream Sockets
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, "1026", &hints, &result)) != 0)
  {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }
  printf("\n\t| Address Received |\n");
  int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  bind(sockfd, result->ai_addr, result->ai_addrlen);
  connect(sockfd, result->ai_addr, result->ai_addrlen);
  printf("\nConnection established!\n");
  char message[100];
  strcpy(message,argv[1]);
  strcat(message," ");
  strcat(message,argv[2]);
  strcat(message," ");
  strcat(message,argv[3]);
  int numOfCharToBeSend = strlen(message);
  printf("\nMessage: %s", message);
  while(numOfCharToBeSend)
  {
    numOfCharToBeSend = numOfCharToBeSend - send(sockfd,message,numOfCharToBeSend*sizeof(char),0);
    printf("\n\tMessage Sent!");

    char *buf = malloc(sizeof(char)*1024);
    int end = recv(sockfd,buf,100,0);
    printf("\n\tResult Received!");
    buf[end] = '\0';
    printf("\nResult: %s \n", buf);
  }
  close(sockfd);
  return 0;
}
