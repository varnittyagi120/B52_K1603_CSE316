#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
int a;
a=100;  //like a shared variable || data of bank 
//T=Number of process U=number of resources
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1=PTHREAD_COND_INITIALIZER;
void calculateneed(int T,int U,int need1[T][U], int maximum[T][U],int allocation[T][U])
{
    for (int i = 0 ; i < T ; i++)
        for (int j = 0 ; j < U ; j++)
            need1[i][j] = maximum[i][j] - allocation[i][j];
    printf("need of processes\n");
    for (int i = 0 ; i < T ; i++)
        {
          for (int j = 0 ; j < U ; j++)
              {
                   printf("%d ",need1[i][j]);
              }
          printf("\n");
        }
}
void function(int *p)
{
    printf("thread %d \n",*p);
    pthread_mutex_lock(&mutex1);
    printf("Updated data of bank %d \n",++a);
    pthread_cond_signal(&cond1); 
    pthread_mutex_unlock(&mutex1);
    pthread_exit(0);  
}
void Safeseq(int T,int U,int process[T], int available[U], int maximum[][U],int allocation[][U])
{
    int i,need1[T][U],count1=0,safesequence[T];
    int kaam[U]; //work
    pthread_t th[T];
    bool sf=true;
     bool f1[T];

    calculateneed(T,U,need1, maximum, allocation);
    for(int i=0;i<T;i++)
       {
          f1[i]=false;
       }
    for (int i = 0; i < U ; i++)
        kaam[i] = available[i];
 while (count1 < T)
  {
       
         bool flag = false;
         for (int i = 0; i < T; i++)
         {
            
             if (f1[i] == false)
             {
               
                int c;
                 for (c= 0; c < U; c++)
                     if (need1[i][c] > kaam[c])
                        break;

                
                 if (c == U)
                 {
                 
                     for (int v= 0 ; v < U ; v++)
                         kaam[v] =kaam[v]+allocation[i][v];

                   
                     safesequence[count1++] = i;

                  
                     f1[i] = true;

                     flag = true;
                }
            }
        }

   
         if (flag== false)
         {
             printf("System is not in safe state");
             sf=false;
             break;
        }
    }
    printf("System is in safe state.\nSafe"
          " sequence is: ");
    for (int i = 0; i < T ; i++)
         printf("%d ",safesequence[i]);
    printf("\n");
    int j=0,k=0,l=0;
  if(sf)
   {  
    pthread_t th[T];
    int g=0;
    for(int i=0;i<T;i++)
     {
      g=safesequence[i];
      pthread_create(&th[safesequence[i]],NULL,function,&g);
      pthread_join(th[safesequence[i]],NULL);
    }
     pthread_mutex_init(&mutex1,NULL);
     while(a<=T)
    {
    pthread_cond_wait(&cond1, &mutex1); 
    }
    pthread_mutex_unlock(&mutex1);
   }
}
int main()
{
int i,j;
int p,r;
printf("Enter the number of processes\n");
scanf("%d",&p);
printf("Enter the number of resources\n");
scanf("%d",&r);
int process[p];
int allocation[p][r];
int max[p][r];
int avail[r];
//printf("Enter processes name or number like 0 ,1 ,2 and soon\n");
for(i=0;i<p;i++)
{
process[i]=i;
}
printf("Enter value for allocation\n");
for(i=0;i<p;i++)
    {
   for(j=0;j<r;j++)
      {
        scanf("%d",&allocation[i][j]);
      }
     }
printf("values of allocation is\n");
for(i=0;i<p;i++)
    {
   for(j=0;j<r;j++)
      {
        printf("%d ",allocation[i][j]);
      }
      printf("\n");
     }
printf("Enter the value of max\n");
for(i=0;i<p;i++)
    {
   for(j=0;j<r;j++)
      {
        scanf("%d",&max[i][j]);
      }
     }
printf("value of max is\n");
for(i=0;i<p;i++)
    {
   for(j=0;j<r;j++)
      {
        printf("%d ",max[i][j]);
      }
      printf("\n");
     }
printf("Enter the available amount\n");
for(i=0;i<r;i++)
{
scanf("%d",&avail[i]);
}
printf("available amount is\n");
for(i=0;i<r;i++)
{
printf("%d \n",avail[i]);
}
Safeseq(p,r,process,avail,max,allocation);
 
    return 0;
}
