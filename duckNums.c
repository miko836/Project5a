#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

const unsigned long MIN_THREADS = 1;
const unsigned long MAX_THREADS = 30;
const unsigned long MIN_LIMIT = 100;
const unsigned long BLOCK = 5000;
unsigned long currCheck = 1;
unsigned long userLimit = 0;
unsigned long duckNumberCount = 0;

void getParams();

void duckCntThread();

int main(int argc, char *argv[]) 
{



    return 0;

}
