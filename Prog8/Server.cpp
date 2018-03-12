/*
  CSE109 Fall 2017
  Peter Brady
  prb315
  Server Connector
  Program 8
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/wait.h>

void sigchld_handler(int num)
{
  printf("in sig handler\n");
  while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char **argv)
{
  if(argc != 2)
    {
      fprintf(stderr, "Incorrect usage: ./Server <filename>\n");
      return 1;
    }
  FILE *fp;
  fp = fopen(argv[1], "rb");
  if(fp == NULL)
    {
      return '\0';
    }
  int mySocket;
  signal(SIGCHLD, sigchld_handler);
  mySocket = socket(AF_INET, SOCK_STREAM, 0);
  if(mySocket == -1)
    {
      fprintf(stderr, "Socket Failed: (%d) %s\n", errno, strerror(errno));
      return 1;
    }
  char sendbuff[250];
  struct sockaddr_in serve;
  memset(&serve, 0, sizeof(struct sockaddr_in));
  memset(sendbuff, 0, sizeof(sendbuff));
  serve.sin_family = AF_INET;
  serve.sin_addr.s_addr = htonl(INADDR_ANY);
  int retry = 1;
  short port = 10000;
  short endport = 10500;

  while(retry)
    {
      if(port > endport)
	{
	  fprintf(stderr, "Could not acquire a port, aborting\n");
	  return 2;
	}
      serve.sin_port = htons(port);
      int bound = bind(mySocket, (struct sockaddr *)&serve, sizeof(struct sockaddr_in));
      if(bound == -1)
	{
	  port++;
	  continue;
	}
      struct linger lin = {0};
      lin.l_onoff = 1;
      lin.l_linger =  10;
      int option = setsockopt(mySocket, SOL_SOCKET, SO_LINGER, (const char*) &lin, sizeof(lin));
      if(option == -1)
	{
	  fprintf(stderr,"Couldn't set linger option\n");
	  return 3;
	}
      if(listen(mySocket, 10) == -1)
	{
	  if(errno == EADDRINUSE)
	    {
	      port++;
	      continue;
	    }
	  fprintf(stderr, "Failed listen (%d): %s \n", errno, strerror(errno));
	  return 4;
	}
      retry = 0;
    }

  printf("port is %d\n", port);
  FILE *connectfp;
  connectfp = fopen("connection.txt", "wb");
  if(fwrite(&port, 2, 1, connectfp) == 0)
    {
      return -1;
    }
  char host[100];
  gethostname(host, sizeof(host));
  size_t a = (sizeof(host) * sizeof(char));
  if(fwrite(&a, 4, 1, connectfp) == 0)
    {
      return -1;
    }
  if(fwrite(&host, a, 1, connectfp) == 0)
    {
      return -1;
    }
  size_t b = (sizeof(argv[1]) * sizeof(char));
  if(fwrite(&b, 4, 1, connectfp) == 0)
    {
      return -1;
    }
  if(fwrite(argv[1], b, 1, connectfp) == 0)
    {
      return -1;
    }
  fclose(connectfp);
  int running = 1;
  int confd = 0;
  struct sockaddr_in otheraddr;
  memset(&otheraddr, 0, sizeof(otheraddr));
  size_t c = sizeof(struct sockaddr_in);
  size_t start;
  size_t amount;
  size_t datasize;
  while(running)
    {
      memset(&otheraddr, 0, sizeof(struct sockaddr_in));
      printf("accepted\n");
      confd = accept(mySocket, (struct sockaddr*)&otheraddr, (socklen_t*)&c);
      printf("connection accepted\n");
      fflush(stdout);
      if(confd == -1)
	{
	  fprintf(stderr, "Accept failed (%d): %s\n", errno, strerror(errno));
	  continue;
	}
      pid_t childID = fork();
      printf("forking\n");
      if(childID == -1)
	{
	  fprintf(stderr, "Failed to fork: %d: %s \n", errno, strerror(errno));
	  return -1;
	}
      if(childID == 0)
	{
	  printf("did we create child\n");
	  if(recv(confd, &datasize, 2, 0) == -1)
	    {
	      return -1;
	    }
	  printf("rec1\n");
	  if((datasize - 10) == 0)
	    {
	      running = 0;
	    }
	  printf("b4 rec2\n");
	  if(recv(confd, &start, 4, 0) == -1)
	    {
	      return -1;
	    }
	  printf("b4 rec3\n");
	  if(recv(confd, &amount, 4, 0) == -1)
	    {
	      return -1;
	    }
	  void *data = (void*)malloc(amount);
	  size_t total;
	  size_t temp;
	  //integrity check
	  for(size_t i = 0; i < (datasize - 10); i+= 2)
	    {
	      printf("b4 rec4\n");
	      if(recv(confd, &temp, 2, 0) == -1)
		{
		  return -1;
		}
	      total += temp;
	    }
	  printf("b4 fseek1\n");
	  if(fseek(fp, start, SEEK_SET) != 0)
	    {
	      return -1;
	    }
	  printf("b4 fseek2\n");
	  if(fread(data, amount, 1, fp) == 0)
	    {
	      return -1;
	    }
	  size_t sentdata;
	  printf("b4 feof\n");
	  if(feof(fp))
	    {
	      sentdata = ftell(fp);
	      sentdata =  sentdata - start;
	    }
	  else
	    {
	      sentdata = amount;
	    }
	  printf("b4 write1\n");
	  if(write(confd, &sentdata, 4) <= 0)
	    {
	      return -1;
	    }
	  printf("b4 write2\n");
	  if(write(confd, &total, 1) <= 0)
	    {
	      return -1;
	    }
	  printf("b4 write3\n");
	  if(write(confd, data, sentdata) <= 0)
	    {
	      return -1;
	    }
	  printf("freeing data\n");
	  free(data);
	  return 0;
	}
    }
  fclose(fp);
  return 0;
}

