#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

int isDuckNumber(long int n) {
    int numOfZeros = 0;

    while (n != 0) {
        if (n % 10 == 0 && n / 10 != 0) {
            numOfZeros++;
        }
        n /= 10;
        //printf("n: %ld", n);
    }
   // printf("numOfZeros: %d", numOfZeros);
    return numOfZeros; 
}


int main(int argc, char *argv[]) 
{

    long int x = 92222012;
    int y = x / 10;

    printf("y: %d", y);

    if(isDuckNumber(x)==1){
        printf("is a duck\n");
    }
    

    return 0;

}
