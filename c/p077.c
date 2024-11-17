//https://projecteuler.net/problem=77
//Prime Summations

#include <stdio.h>
#define MAX 1000000

int IS_PRIME[MAX] = {0};
int primes[2097152];
int numPrimes;

void sieve() {
    numPrimes = 0;
    for (int i = 2; i<= MAX; i++)
    {
        if (!IS_PRIME[i]) {
            for (int j = 2; i * j<= MAX; j++)
                IS_PRIME[i * j]= 1;
        }
    }

    for (int i = 2; i<MAX;i++) {
        if (!IS_PRIME[i]) {
            primes[numPrimes] = i;
            numPrimes++;
        }
    }
}

int primeWays(int n, int max) {
    int s = 0;
    if (n < 0) {
        return 0;
    }
    if (n ==0) {
        return 1;
    }
    for (int i = 1; primes[i]<=max; i++) {
        s += primeWays(n - primes[i], primes[i]);
    }
    return s;
}

int main(void) {
    sieve();
    int i = 10;
    while (primeWays(i,i)<=5000) {
        i++;
    }
    printf("%d\n",i);
    return 0;
}