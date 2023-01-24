#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int times = 0;
void* func(void *arg)
{
   long long *p = (long long*)arg;
   int i = 0;
   while(i<times)
   {
       *p-=2;
       i++;
    }
    pthread_exit(NULL);
}
 
int main(int argc,char *argv[])
{
  long long counter = 0;
  pthread_t pid;
  int j = 0;
  if(argc<2)
     return -1;
  else
     times = atoi(argv[1]);
   pthread_create(&pid,NULL,&func,(void*)&counter);
   while(j<times)
   {
     counter-=2;
     j++;
   }
   pthread_join(pid,NULL);
   printf("%lld\n",counter);
   return 0;
} 
