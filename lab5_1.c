#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#define BUF_SZ 6

struct mybuffer{
   int in;
   int out;
   long  int buf[BUF_SZ];
};
  int main(int argc, char *argv[])
{
    int n;
    pid_t pid;
    int shm;
    struct mybuffer *shmptr;
    if(argc >1)
       n = atoi(argv[1]);
    srand((unsigned)time(NULL));
    shm = shmget(IPC_PRIVATE,sizeof(struct mybuffer),IPC_CREAT|0660);//create shared memory
    shmptr = shmat(shm,NULL,0);//attach the shared memory to the pointer
    shmptr -> in = 0;
    shmptr -> out = 0;
    pid = fork();
    if(pid == 0)//child process as the producer
    {
      int count = 0;
      int num = 1;
      float sec;
      while(count<n)
      {
        if(count>0)
         num = num * count;
        while((shmptr->in+1)%BUF_SZ==shmptr->out);
        shmptr->buf[shmptr->in] = num;
        shmptr->in = (shmptr->in+1)%BUF_SZ; 
        sec = rand()/RAND_MAX+3.0;
        sleep(sec);
        count++;
       }
     }
     else//parent process as the consumer
     {
        int count = 0;
        while(count<n)
        {
          while(shmptr->in==shmptr->out);
          printf("%ld\n",shmptr->buf[shmptr->out]);
          fflush(stdout);
          shmptr->out = (shmptr->out+1)%BUF_SZ;
          count++;
        }
      }
      return 0;

}     
