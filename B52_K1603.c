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