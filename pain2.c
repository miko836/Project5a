#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>


#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define MIN_THREADS 1
#define MAX_THREADS 30
#define MIN_LIMIT 100
#define BLOCK_SIZE 5000

unsigned long current_number = 1;
unsigned long user_limit = 0;
unsigned long duck_number_count = 0;
unsigned long thread_count = 0;
pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;

void getParams(int argc, char *argv[]);
void *duck_count_thread(void *arg);
void create_and_join_threads(unsigned long thread_num, pthread_t *threads, pthread_attr_t *attr);

int main(int argc, char *argv[]) {
    getParams(argc, argv);

       user_limit = atoi(argv[4]);
     thread_count = atoi(argv[2]);


    printf("CS 370 - Project #2\nDuck Numbers Program\n\n");
    printf("Hardware Cores: 6\n");
    printf("Thread count: %ld\n", thread_count);
    printf("Numbers Limit: %ld\n", user_limit);
    printf("\nPlease wait. Running...\n\n");

    pthread_t threads[thread_count];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    create_and_join_threads(thread_count, threads, &attr);

    printf("Count of Duck numbers from 1 to %ld is %ld", user_limit, duck_number_count);

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&global_mutex);

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
        printf("Error, limit must be > %d.\n", MIN_LIMIT);
        exit(1);
    }   


}


void *duck_count_thread(void *arg) {
    unsigned long start, end;
    int zeros;

    pthread_mutex_lock(&global_mutex);
    start = current_number;
    end = current_number + BLOCK_SIZE - 1;
    current_number += BLOCK_SIZE;
    pthread_mutex_unlock(&global_mutex);

    for (unsigned long i = end; i >= start; i--) {
        zeros = 0;
        unsigned long temp = i;
        while (temp != 0) {
            if (temp % 10 == 0 && temp / 10 != 0) {
                zeros++;
            }
            temp /= 10;
        }
        if (zeros == 1) {
            pthread_mutex_lock(&global_mutex);
            duck_number_count++;
            pthread_mutex_unlock(&global_mutex);
        }
    }

    pthread_exit(NULL);
}

void create_and_join_threads(unsigned long thread_num, pthread_t *threads, pthread_attr_t *attr) {
    for (unsigned long i = 0; i < thread_num; i++) {
        if (pthread_create(&threads[i], attr, duck_count_thread, NULL) != 0) {
            fprintf(stderr, "Error creating thread %lu\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (unsigned long i = 0; i < thread_num; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread %lu\n", i);
            exit(EXIT_FAILURE);
        }
    }
}