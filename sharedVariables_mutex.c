#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_THREADS 10000

pthread_mutex_t globalVariable_mutex;
int globalVariable = 0;

void *sampleWork_add (void *args) 
{
	int localVariable = rand() % 10;
	long *tid_addr = (long*)args;
	long tid = *tid_addr;
	
	pthread_mutex_lock(&globalVariable_mutex);
	globalVariable = globalVariable + 1;
	pthread_mutex_unlock(&globalVariable_mutex);
	
	printf("thread id = %ld; \t Local Variable = %d; \t global Variable = %d \n", tid, localVariable, globalVariable);
	
	pthread_exit(args);
}

void *sampleWork_sub (void *args) 
{
	int localVariable = rand() % 10;
	long *tid_addr = (long*)args;
	long tid = *tid_addr;
	
	pthread_mutex_lock(&globalVariable_mutex);
	globalVariable = globalVariable - 1;
	pthread_mutex_unlock(&globalVariable_mutex);
	printf("thread id = %ld; \t Local Variable = %d; \t global Variable = %d \n", tid, localVariable, globalVariable);
	
	pthread_exit(args);
}

int main () {
	pthread_t thread[NUM_THREADS];
	pthread_attr_t thread_attr;
	
	long tid = 0;
	srand(time(NULL));
	
	pthread_attr_init(&thread_attr);
	
	for (; tid < NUM_THREADS/2; tid++) 
	{
		if (pthread_create(&thread[tid], &thread_attr, sampleWork_add, &tid))
		{
			printf("Error creating thread %ld \n", tid);
			exit (-1);
		}
	}
	
	for (; tid < NUM_THREADS; tid++) 
	{
		if (pthread_create(&thread[tid], &thread_attr, sampleWork_sub, &tid))
		{
			printf("Error creating thread %ld \n", tid);
			exit (-1);
		}
	}
	
	for (tid = 0; tid < NUM_THREADS; tid++)
	{
		if (pthread_join(thread[tid], NULL))
		{
            printf("Error joining thread %d: \n", tid);
		}
	}
	
	printf("Global Variable = %d\n", globalVariable);
}
