//https://projecteuler.net/problem=231
//Prime Factorisation of Binomial Coefficients

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define A 20000000
#define B 15000000

long vp(int n, int p) {
    //returns max a such that p^a | n!
    long ret = 0;
    while (n > 0) ret += (n /= p);
    return ret;
}

int main(void) {
    unsigned char *IS_PRIME = calloc(A+1, sizeof(unsigned char));
    int *primes = calloc(1.1*(double) A / log(A),sizeof(int));
    int numPrimes = 0;
    for (int p = 2; p<=A; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<=A; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    long ans = 0;
    for (int i = 0; i<numPrimes; i++) {
        long t = 0;
        t += vp(A, primes[i]);
        t -= vp(B, primes[i]);
        t -= vp(A-B, primes[i]);
        ans += t*primes[i];
    }
    printf("%ld\n", ans);
    free(primes);
    free(IS_PRIME);
    return 0;
}