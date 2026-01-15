//https://projecteuler.net/problem=249
//Prime Subset Sums

#include <stdio.h>
#include <stdlib.h>
#define MOD 10000000000000000
#define N 5000

int primes[1000];
int numPrimes = 0;

int isPrime(int num) {
    if (num < 2) return 0;
    if (num <= 3) return 1;
    for (int i = 2; i*i<=num; i++)
        if (num % i == 0) return 0;
    return 1;
}

int main(void) {
    int max = 0;
    for (int i = 2; i < 5000; i++) {
        if (isPrime(i)) {
            primes[numPrimes++] = i;
            max += i;
        }
    }
    long *numRepr = calloc(max+1, sizeof(long));
    int m = 0;
    numRepr[0] = 1;
    for (int i = 0; i<numPrimes; i++) {
        int p = primes[i];
        m += p;
        for (int j = m; j>=p; j--) {
            numRepr[j] += numRepr[j-p];
            numRepr[j] %= MOD;
        }
    }
    long ans = 0;
    for (int i = 2; i<max; i++) {
        if (isPrime(i)) {
            ans += numRepr[i];
            ans %= MOD;
        }
    }
    printf("%ld\n", ans);
    free(numRepr);
    return 0;
}