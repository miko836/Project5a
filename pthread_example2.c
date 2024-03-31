#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_THREADS 10

void *sampleWork (void *args) 
{	
	long *tid_addr = (long*)args;
	long tid = *tid_addr;
	
	printf("Hello from a thread %ld\n", tid);
	pthread_exit(args);
}

int main () {
	pthread_t thread[NUM_THREADS];
	pthread_attr_t thread_attr;
	pthread_attr_init(&thread_attr);
	
	int tid= 0;
	
	for (; tid < NUM_THREADS; tid++) 
	{
		if (pthread_create(&thread[tid], &thread_attr, sampleWork, &tid))
		{
			printf("Error creating thread %d \n", tid);
			exit (-1);
		}
	}
	
	for (tid = 0; tid < NUM_THREADS; tid++)
	{
		if (pthread_join(thread[tid], NULL))
		{
			printf("Error joining thread %d\n", tid);
		}
	}

}
