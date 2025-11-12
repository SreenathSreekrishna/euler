//https://projecteuler.net/problem=187
//Semiprimes

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    //first i just generate all primes < 5*10^7 and then just bruteforce check all primes.
    unsigned char *IS_PRIME = malloc(sizeof(unsigned char) * 50000000);
    int *primes = malloc(sizeof(int) * 5000000);
    int numPrimes = 0;
    for (int p = 2; p<50000000; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<50000000; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    free(IS_PRIME);

    long ans = 0;
    for (int i = 0; i<numPrimes; i++)
        for (int j = i; j<numPrimes && (long) primes[i]*primes[j] < 1e8; j++)
            ans++;

    printf("%ld\n", ans);

    free(primes);
    return 0;
}