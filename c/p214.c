//https://projecteuler.net/problem=214
//Totient Chains

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 25
#define BOUND 40000000

int phi[BOUND+1] = {0};

int main(void) {
    unsigned char *IS_PRIME = calloc(BOUND+1, sizeof(unsigned char));
    int *primes = calloc(1.1*(double) BOUND / log(BOUND),sizeof(int));
    int numPrimes = 0;
    for (int p = 2; p<=BOUND; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<=BOUND; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
            phi[p] = p-1;
        }
    }
    phi[1] = 1;
    for (int i = 2; i<=BOUND; i++) {
        if (!IS_PRIME[i]) continue;
        int j = 0;
        while (i%primes[j]) j++;
        int n = i;
        long power = 1;
        while (n%primes[j] == 0) {
            n/=primes[j];
            power *= primes[j];
        }
        phi[i] = (primes[j]-1) * power/primes[j] * phi[n];
    }

    long ans = 0;

    for (int i = 0; i<numPrimes; i++) {
        int steps = 1;
        int curr = primes[i];
        while (curr != 1) {
            curr = phi[curr];
            steps++;
            if (steps >= N+1) break;
        }
        if (steps == N) ans += primes[i];
    }

    printf("%ld\n", ans);

    free(IS_PRIME);
    free(primes);
    return 0;
}