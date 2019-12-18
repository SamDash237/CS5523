/*
Sam Dash
eeo072
CS 5523
Homework 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define array_size 10 //when changing contents of thread_list, change this value as well
#define THREAD_COUNT 3

void *sort_thread (void *parmtr);
void *merge_thread (void *parmtr);

int thread_list[array_size] = {7,12,19,3,18,4,2,6,15,8}; //change this to change list, and adjust array_size accordingly
int thread_result[array_size];

typedef struct
{
  int from_i;
  int to_i;
} parameter;

int main (int argc, const char * argv[])
{
  int i;
  pthread_t threaders[THREAD_COUNT];
  
  //first sorting thread
  parameter *thread_data = (parameter *)malloc(sizeof(parameter));
  thread_data->from_i = 0;
  thread_data->to_i = (array_size/2) - 1;
  pthread_create(&threaders[0], 0, sort_thread, thread_data);
  
  //second sorting thread
  thread_data = (parameter *)malloc(sizeof(parameter));
  thread_data->from_i = (array_size/2);
  thread_data->to_i = array_size - 1;
  pthread_create(&threaders[1], 0, sort_thread, thread_data);
  
  //wait for sorting threads to finish
  for (i = 0; i < THREAD_COUNT; i++)
    pthread_join(threaders[i], NULL);
    
  //merge thread
  thread_data = (parameter *)malloc(sizeof(parameter));
  thread_data->from_i = 0;
  thread_data->to_i = array_size - 1;
  pthread_create(&threaders[2], 0, merge_thread, thread_data);
  
  //wait for merge thread to finish
  pthread_join(threaders[2], NULL);
  
  //output sorted array
  return 0;
}

void *sort_thread(void *parmtr)
{
  parameter *p = (parameter *)parmtr;
  
  int start = p->from_i;
  int finish = p->to_i + 1;
  
  int z;
  for(z = start; z < finish; z++)
    printf("The integer received is: %d\n", thread_list[z]);
    
  printf("\n");
  
  int a, b, c, d;
  
  for(a = start; a < finish; a++)
  {
    for(b = start; b < finish-1; b++)
    {
      if(thread_list[b] > thread_list[b+1])
      {
        c = thread_list[b];
        thread_list[b] = thread_list[b+1];
        thread_list[b+1] = c;
      }
    }
  }
  
  for(d = start; d < finish; d++)
    printf("The sorted integer array: %d\n", thread_list[d]);
  
  int x;

  for(x = start; x < finish; x++)
    thread_result[x] = thread_list[x];

  printf("\n");
  pthread_exit(NULL);
}

void *merge_thread (void *parmtr)
{
  parameter *p = (parameter *)parmtr;
  
  int start_val = p->from_i;
  int finish_val = p->to_i + 1;  
  
  int a,b,c;
  
  for(a = start_val ; a < finish_val; a++)
  {
    for(b = start_val ; b < finish_val-1; b++)
    {
      if(thread_result[b] > thread_result[b+1])
      {
        c = thread_result[b];
        thread_result[b] = thread_result[b+1];
        thread_result[b+1] = c;
      }
    }
  }
  
  int d;
  for(d = start_val ; d < finish_val; d++)
    printf("Final result array is: %d\n", thread_result[d]);
  pthread_exit(NULL);
}