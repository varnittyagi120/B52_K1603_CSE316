#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
int a;
a=100;  //like a shared variable || data of bank 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void calculateneed(int P,int R,int need[P][R], int max[P][R],int allocation[P][R])
{
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    printf("need of processes\n");
    for (int i = 0 ; i < P ; i++)
        {
          for (int j = 0 ; j < R ; j++)
              {
                   printf("%d ",need[i][j]);
              }
          printf("\n");
        }
}
void function(int *p)
{
    printf("thread %d \n",*p);
    pthread_mutex_lock(&mutex);
    printf("Updated data of bank %d \n",++a);
    pthread_cond_signal( &cond ); 
    pthread_mutex_unlock( & mutex );
    pthread_exit(0);  
}

void Safeseq(int P,int R,int processes[P], int avail[R], int maxm[][R],int allot[][R])
{
    int i;
    pthread_t th[P];
    bool sf=true;
    int need[P][R];

    calculateneed(P,R,need, maxm, allot);

  
    bool finish[P];
    for(int i=0;i<P;i++)
       {
          finish[i]=false;
       } 

   
    int safeSeq[P];

    
    int work[R];
    for (int i = 0; i < R ; i++)
        work[i] = avail[i];

     int count = 0;
     while (count < P)
     {
       
         bool found = false;
         for (int p = 0; p < P; p++)
         {
            
             if (finish[p] == false)
             {
               
                int j;
                 for (j = 0; j < R; j++)
                     if (need[p][j] > work[j])
                        break;

                
                 if (j == R)
                 {
                 
                     for (int k = 0 ; k < R ; k++)
                         work[k] =work[k]+allot[p][k];

                   
                     safeSeq[count++] = p;

                  
                     finish[p] = true;

                     found = true;
                }
            }
        }

   
         if (found == false)
         {
             printf("System is not in safe state");
             sf=false;
             break;
        }
    }
    printf("System is in safe state.\nSafe"
          " sequence is: ");
    for (int i = 0; i < P ; i++)
         printf("%d ",safeSeq[i]);
    printf("\n");
    int j=0,k=0,l=0;
 if(sf)
   {  
    pthread_t th[P];
    int g=0;
    for(int i=0;i<P;i++)
     {
      g=safeSeq[i];
      pthread_create(&th[safeSeq[i]],NULL,function,&g);
      pthread_join(th[safeSeq[i]],NULL);
    }
     pthread_mutex_init(&mutex,NULL);
     while(a<=P)
    {
    pthread_cond_wait( & cond, & mutex ); 
    }
    pthread_mutex_unlock( & mutex );
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
