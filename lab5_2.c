#include <sys/types.h> 
#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define BUF_SZ 6
#define READ_END 0
#define WRITE_END 1
int main(int argc, char *argv[])
{  
   int n; 
   pid_t  pid;
   int  fd[2];
   char write_msg[100];
   char read_msg[100];
   float sec;
   srand((unsigned)time(NULL)); 
   if(argc>1)
      n = atoi(argv[1]);
   if(pipe(fd) == -1)
   {
     fprintf(stderr,"Pipe failed");
     return -1;
   }
   pid = fork();
   if(pid<0)
   {
      fprintf(stderr,"Fork Failed");
      return 1;
   }
   else if(pid>0)//parent process as the consumer
   {
       close(fd[WRITE_END]);
       int count = 0;
       long int num;
       while(count<n)
       {
          read(fd[READ_END],read_msg,100);
          num = atoi(read_msg);
          printf("%ld\n",num);
          fflush(stdout);
          count++;
       }
       close(fd[READ_END]);
   }
   else//child process as the producer
   {
       close(fd[READ_END]);
       int count = 0;
       long int num = 1;
       while(count<n)
       {
          if(count==0)
             num = 1;
          else
             num = num * count;
          sprintf(write_msg,"%ld",num);
          write(fd[WRITE_END],write_msg,100);
          memset(write_msg,'\0',100);
          count++;
          sec = rand()/(RAND_MAX+3.0);
          sleep(sec);
        }
       close(fd[WRITE_END]);
    }
    return 0;
}
