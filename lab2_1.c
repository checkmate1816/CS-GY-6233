#include <fcntl.h> 
#include <unistd.h>
#include <stdio.h>
#define BUFFSIZE 4096
#define PERM 0666
int main()
{
  int n;
  char buf[BUFFSIZE]; 
  int source;
  int destination;
  char  sourcename[100];
  char  destinationname[100];
  printf("Please insert source file's name\n");
  scanf("%s",sourcename);
  printf("Please insert destination file's name\n");
  scanf("%s",destinationname);
  source = open(sourcename,O_RDONLY);//open source file
  if(source<0)
    _exit(-1);
  destination = creat(destinationname,PERM);//create destination file
  if(destination<0)
     _exit(-1);
  while((n = read(source,buf,BUFFSIZE))>0)//copy content from the source file to the destination file
      if(write(destination,buf,n) != n)
           _exit(-1);
  if(n < 0)
     _exit(-1);
  close(source);//close source file
  close(destination);//close destination file
  return 0;
}

