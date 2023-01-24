#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define SOCK_FILE "/tmp/sock"

long int factorial(int n)
{
   if(n==0)
      return 1;
   return n*factorial(n-1);
}

int main(int argc, char *argv[])
{
    int n;
    if(argc != 2)
     {
      printf("arguments not enough\n");
      return -1;
     }
    
    n = atoi(argv[1]);
    srand((unsigned)time(NULL));
    
    struct sockaddr_un ser_addr, cli_addr;
    memset(&ser_addr,0,sizeof(struct sockaddr_un));
    ser_addr.sun_family = AF_LOCAL;
    strncpy(ser_addr.sun_path,SOCK_FILE,sizeof(ser_addr.sun_path)-1);
    
    pid_t pid = fork();

    if(pid<0)
    {
       printf("Fork failed!\n");
       return -1;
    }
    else if( pid == 0 )
    {
      int server = socket(AF_LOCAL,SOCK_STREAM,0);
      if( server < 0)
      {
          printf("server socket create failed\n");
          return -1;
      }
      if(bind(server,(struct sockaddr*)&ser_addr,sizeof(struct sockaddr_un))==-1)
      {
         printf("bind server socket error\n");
         return -1;
      }
      int  time = rand()%5  + 1;
      socklen_t cli_addr_size = sizeof(struct sockaddr_un);
      sleep(time);
      listen(server,5);
      int accept_socket = accept(server,(struct sockaddr *)&cli_addr,&cli_addr_size);
      int c = 0;
      while(c<n)
      {
        long int val = factorial(c);
        write(accept_socket,&val,sizeof(long int));
        c++;
      }
      close(server);
      close(accept_socket);
      unlink(SOCK_FILE);
     }
     else
     {
         int client = socket(AF_LOCAL,SOCK_STREAM,0);
         while(connect(client,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_un))==-1)
         {
             sleep(0.1);
         }
         int c = 0;
         long int val = 0;
         while(c<n)
         {
           read(client,&val,sizeof(long int));
           printf("%ld\n",val);
           fflush(stdout);
           c++;
         }
         close(client);
    }
    return 0;
} 
