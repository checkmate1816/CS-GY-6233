#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <ctype.h>
#include <errno.h>
#include <sys/mman.h>

int n =1;
int checkDigit(char *str){
    for(int i = 0;i<strlen(str);i++){
        if(!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int main(int argc,char *argv[])
{
   if(argc!=2)
  {
    printf("argument error\n");
    return -1;
  }
  
  if(!checkDigit(argv[1])){
        printf("integer parameters only!\n");
        return -1;
    }
  
  n = atoi(argv[1]);
  
  printf("This is the address of n: %p\n",&n);

  int fd = shm_open("lab9_shm",O_CREAT|O_RDWR,0777);//open the file
  if(fd == -1)
   {
      printf("open error\n");
      char *msg = strerror(errno);
      printf("%s\n",msg);
      return -1;
   }
 
   long int *buf = (long int*)mmap(NULL,sizeof(long int)*n,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  
   if(buf == MAP_FAILED)
   {
      char *msg = strerror(errno);
      printf("%s\n",msg);
      return -1;
   }
  printf("This is the start address of the shared buffer: %p\n",buf);
   
   int i = 0;
  
   while(i<n)
   {
      printf("%ld\n",buf[i]);
      i++;
   }
   return 0;
}

