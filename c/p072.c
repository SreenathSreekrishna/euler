//https://projecteuler.net/problem=72
//Counting Fractions

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

int phi(int n) {
    int p = n;
    for (int i = 0; primes[i]*primes[i] <= n; i++) {
        if (n % primes[i]== 0) {
            p /= primes[i];
            p *= (primes[i] - 1);
 
            while (n % primes[i]== 0)
               n /= primes[i];
        }
    }

    if (n>1) {
        p -= p/n;
    }

 
    return p;
}

int main(void) {
    sieve();
    long n = 0;
    for (int d = 2; d<=MAX; d++) {
        n += phi(d);
    }
    printf("%ld\n", n);
    return 0;
}