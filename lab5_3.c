#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUF_SZ 6

pthread_mutex_t mutex;
long int buf[BUF_SZ];
int in = 0;
int out = 0;
void *runner(void *param)
{
   int n = *(int*)param;
   int num = 1;
   int count = 0;
   float sec;
   srand((unsigned)time(NULL));
   while(count<n)
   {
     if(count == 0)
       num = 1;
     else
       num = num * count;
     while((in+1)%BUF_SZ==out);
     pthread_mutex_lock(&mutex);
     buf[in] = num;
     in = (in+1)%BUF_SZ;
     pthread_mutex_unlock(&mutex);
     sec = rand()/(RAND_MAX+3.0);
     sleep(sec);
     count++;
    }
    pthread_exit(0);
}
int main(int argc, char *argv[])
{
    int n;
    pthread_t tid;
    int count = 0;
    if(argc>1)
      n = atoi(argv[1]);

    pthread_create(&tid,NULL,runner,(void*)&n);//child thread as the producer
    while(count<n)//main thread as the consumer
    {
       while(in==out);
       pthread_mutex_lock(&mutex);
       printf("%ld\n",buf[out]);
       fflush(stdout);
       out = (out+1)%BUF_SZ;
       pthread_mutex_unlock(&mutex);
       count++;
    }
    return 0;
}

