#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

const unsigned long MIN_THREADS = 1;
const unsigned long MAX_THREADS = 30;
const unsigned long MIN_LIMIT = 100;
const unsigned long BLOCK = 5000;
unsigned long currCheck = 1;
unsigned long userLimit = 0;
unsigned long duckNumberCount = 0;
unsigned long threadCount = 0;

void getParams(int argc, char *argv[]);

int duckCntThread(unsigned long n, int BLOCK);

int main(int argc, char *argv[]) 
{

    getParams(argc, argv);

    printf("CS 370 - Project #2\nDuck Numbers Program\n\n");

    printf("Hardware Cores: 6\n");
    printf("Thread count:   %d\n", atoi(argv[2]));
    printf("Numbers Limit:  %d\n", atoi(argv[4]));

    printf("\nPlease wait. Running...\n\n");

    unsigned long ourLimit = atoi(argv[4]);




	pthread_t thread[atoi(argv[2])];
	pthread_attr_t thread_attr;
	pthread_attr_init(&thread_attr);
	
	int tid= 0;
	
    while (currCheck < ourLimit)
    {

	for (; tid < atoi(argv[2]); tid++) 
	{
		if (pthread_create(&thread[tid], &thread_attr, duckCntThread(currCheck, BLOCK), NULL))
		{
			printf("Error creating thread %d \n", tid);
			exit (-1);
		}
	}

	for (tid = 0; tid < atoi(argv[2]); tid++)
	{
		if (pthread_join(thread[tid], NULL))
		{
			printf("Error joining thread %d\n", tid);
		}
	}


    }   



	
	for (tid = 0; tid < atoi(argv[2]); tid++)
	{
		if (pthread_join(thread[tid], NULL))
		{
			printf("Error joining thread %d\n", tid);
		}
	}

}









    while (currCheck < ourLimit)
    {
        duckNumberCount += duckCntThread(currCheck, BLOCK);
        currCheck += BLOCK;

    }
    
    printf("Count of Duck numbers from 1 to %ld is %ld\n", ourLimit, duckNumberCount);

    return 0;

}

void getParams(int argc, char *argv[]){

    char *endptr;

    if (argc == 1)
    {
        printf("Usage: ./duckNums -th <threadCount> -lm <limitValue>\n");
        exit(1);
    }

    if (argc != 5)
    {
        printf("Error, invalid command line options.\n");
        exit(1);
    }
    
    if (strcmp(argv[1], "-th"))
    {
        printf("Error, invalid thread count specifier.\n");
        exit(1);
    }

    strtol(argv[2], &endptr, 10);
    if (*endptr != '\0')
    {
        printf("Error, invalid thread count value.\n");
        exit(1);
    }

    if (atoi(argv[2]) > MAX_THREADS)
    {
        printf("Error, thread count out of range.\n");
        exit(1);
    }

    if (strcmp(argv[3], "-lm"))
    {
        printf("Error, invalid limit specifier.\n");
        exit(1);
    }

    strtol(argv[4], &endptr, 10);
    if (*endptr != '\0')
    {
        printf("Error, invalid limit value.\n");
        exit(1);
    }

    if (atoi(argv[4]) < MIN_LIMIT)
    {
        printf("Error, limit must be > %ld.\n", MIN_LIMIT);
        exit(1);
    }   


}

int duckCntThread(unsigned long n, int BLOCK){

    int numOfZeros = 0;
    int limitStop = n + BLOCK - 1;
    int numDuck = 0;
    int i = limitStop;

for (i; i != n ; i--)
{

    limitStop = i;

    numOfZeros = 0;

    while (limitStop != 0) {
        if (limitStop % 10 == 0 && limitStop / 10 != 0) {
            numOfZeros++;
        }
        limitStop /= 10;
        //printf("n: %ld", n);
    }

  //  printf("%d\n", limitStop);

    if (numOfZeros == 1)
    {
        numDuck++;
    }
    

}





   // printf("numOfZeros: %d", numOfZeros);
    return numDuck; 

}