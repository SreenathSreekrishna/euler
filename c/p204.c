//https://projecteuler.net/problem=204
//Generalised Hamming Numbers

#include <stdio.h>
#include <stdlib.h>
#define BOUND 1e9
#define TYPE 100

int *primes;
int numPrimes = 0;

long numPossibilities(int minIndex, long bound) {
    if (bound == 0) return 0;
    long ret = 1;
    for (int i = minIndex; i<numPrimes; i++) {
        ret += numPossibilities(i, bound / primes[i]);
    }
    return ret;
}

int main(void) {
    unsigned char *IS_PRIME = malloc(sizeof(unsigned char) * (TYPE+1));
    primes = malloc(sizeof(int) * 1024);
    for (int p = 2; p<=TYPE; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<=TYPE; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    free(IS_PRIME);
    printf("%ld\n", numPossibilities(0, BOUND));
    free(primes);
    return 0;
}