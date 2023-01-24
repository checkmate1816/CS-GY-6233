#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <limits.h>
#include <ctype.h>

int checkDigit(char *str){
  for(int i=0;i<strlen(str);i++){
    if(!isdigit(str[i]))
       return 0;
   }
   return 1;
}

void clear(int* page,int f)
{
  int index = 0;
  while(index<f)
  {
     page[index] = -1;
     index ++;
  }
}

int checkposition(int* page,int num,int f)
{
   int index = 0;
   while(index < f)
   {
      if(page[index] == num)
        return index;
      index++;
   }
   return -1;
}

int find(int* page,int f,int arr[],int cur)
{
   int index = 0;
   int max = INT_MIN;
   int pos = 0; // pos means the index which will be swapped out
   int step = 0; // step means the max step to get the next same number 
   while(index < f)
   {
       int num = page[index];
       step = 1;
       while((arr+cur+step)!=NULL)
       {
          if(arr[cur+step]==num)
               break;
          else 
            step++;
       }
       if(step > max)
       {
           max = step;
           pos = index;
       }
             
       index++;
   }
   return pos;
}
    
int replace(int* page,int arr[],int n,int f)
{
   int index = 0;
   int  num = 0;
   while(index < n)
  {
     int pos = checkposition(page,arr[index],f);
     if(pos == -1)
     {
       num ++;
       pos = find(page,f,arr,index);
       page[pos] = arr[index];
     }
     index++;
   }
   return num;
}
  
int main(int argc, char* argv[])
{
   int n;
   int k;
   int* arr = NULL; 
   int index = 0;
   int f = 0;
   int * page = NULL;
   int times = 100;
   FILE * fp;
   
   if(argc!=3){
    printf("argument error\n");
    return -1;
   }

   if(!checkDigit(argv[1])||!checkDigit(argv[2]))
   {
     printf("Integers parameters only!\n");
     return -1;
   }
   n = atoi(argv[1]);
   k = atoi(argv[2]);

   if(n<16||k<8)
   {
     printf("Number is so small.\n");
     return -1;
   }
   
   if((n&(n-1)!=0)||(k&(k-1))!=0)
   {
     printf("Number is not power of 2.\n");
     return -1;
   } 
   arr = (int*)malloc(sizeof(int)*n);
   srand((unsigned)time(NULL));

   while(index < n)
   {
     *(arr+index) = rand()%k;
     index++;
   }//produce sequence of numbers 
   
   fp = fopen("file.txt","w+"); 
   index = 0;
   while(index < times)
   { 
     f = rand()%(k-3) + 4;//produce random number of pages
     page = (int*)malloc(f*sizeof(int));//allocate memory for pages
     clear(page,f);//clear pages
     int errors = replace(page,arr,n,f);
     fprintf(fp,"%d %d\n",f,errors);
     free(page);
     index++;
   }
   free(arr);
   fclose(fp);
   return 0;
}
