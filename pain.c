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
pthread_mutex_t globalVariable_mutex;


void getParams(int argc, char *argv[]);

void duckCntThread();

int main(int argc, char *argv[]) 
{

    getParams(argc, argv);

    printf("CS 370 - Project #2\nDuck Numbers Program\n\n");

    printf("Hardware Cores: 6\n");
    printf("Thread count:   %d\n", atoi(argv[2]));
    printf("Numbers Limit:  %d\n", atoi(argv[4]));

    printf("\nPlease wait. Running...\n\n");

    unsigned long ourLimit = atoi(argv[4]);

	// pthread_t thread[atoi(argv[2])];
	// pthread_attr_t thread_attr;
	// pthread_attr_init(&thread_attr);
	
	// int tid = 0;
	







    while (currCheck < ourLimit)
    {

	// for (; tid < atoi(argv[2]); tid++) 
	// {
	// 	if (pthread_create(&thread[tid], &thread_attr, duckCntThread, &tid))
	// 	{
	// 		printf("Error creating thread %d \n", tid);
	// 		exit (-1);
	// 	}
	// }

    //    printf("\nEnd of create. \n\n");

    duckCntThread();

	// for (tid = 0; tid < atoi(argv[2]); tid++)
	// {
	// 	if (pthread_join(thread[tid], NULL))
	// 	{
	// 		printf("Error joining thread %d\n", tid);
	// 	}
	// }

       // printf("\nEnd of join. \n\n");

    }   

    printf("Duck count: %ld", duckNumberCount);

return 0;
}









//     while (currCheck < ourLimit)
//     {
//         duckNumberCount += duckCntThread(currCheck, BLOCK);
//         currCheck += BLOCK;

//     }
    
//     printf("Count of Duck numbers from 1 to %ld is %ld\n", ourLimit, duckNumberCount);

//     return 0;

// }

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

void duckCntThread(){

    int numOfZeros = 0;
    int currTmp = 0;



	//pthread_mutex_lock(&globalVariable_mutex);
    int limitStop = currCheck + BLOCK - 1;
    currCheck += BLOCK;
    currTmp = currCheck - 5000;
	//pthread_mutex_unlock(&globalVariable_mutex);


    printf("Currcheck: %ld\n", currCheck);
    printf("CurrTmp: %d\n", currTmp);

    int i = limitStop;

    printf("limitStop: %d\n", limitStop);


for (i; i != currTmp ; i--)
{


    limitStop = i;

    numOfZeros = 0;

    while (limitStop != 0) {
        if (limitStop % 10 == 0 && limitStop / 10 != 0) {
            numOfZeros++;
        }
        limitStop /= 10;
        // printf("n: %d\n", currTmp);
    }

    // printf("i: %d\n", i);
    // printf("limitStop: %d\n", limitStop);

    if (numOfZeros == 1)
    {
	    
        //pthread_mutex_lock(&globalVariable_mutex);
        duckNumberCount++;
	   // pthread_mutex_unlock(&globalVariable_mutex);

    }
    
    

}



}