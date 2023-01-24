#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <semaphore.h>

sem_t mutex;
void* calculate(void* num)
{
   double x;
   double y;
   double distance;
   int times = 0;
   while(times<1000000)
   {
     x = (rand()/(double)(RAND_MAX))*2 -1;
     y = (rand()/(double)(RAND_MAX))*2 -1;
     distance = sqrt(x*x+y*y);
     if(distance <= 1.0)
     {
       sem_wait(&mutex);
       (*(int*)num)++;
       sem_post(&mutex);
     }
     times++;
   }
}
     
   
int main()
{
  srand((unsigned)time(NULL));
  pthread_t worker1;
  pthread_t worker2;
  pthread_t worker3;
  pthread_t worker4; 
  int num = 0;
  double area = 0;
  sem_init(&mutex,0,1);
  
  pthread_create(&worker1,NULL,calculate,(void*)&num);
  pthread_create(&worker2,NULL,calculate,(void*)&num);
  pthread_create(&worker3,NULL,calculate,(void*)&num);
  pthread_create(&worker4,NULL,calculate,(void*)&num);
  
  pthread_join(worker1,NULL);
  pthread_join(worker2,NULL);
  pthread_join(worker3,NULL);
  pthread_join(worker4,NULL);
  
  area = 4 *((double)num/4000000);
  printf("%lf\n",area);
  return 0;
}
