//https://projecteuler.net/problem=200
//Prime-proof Squbes

#include <stdio.h>
#include <stdlib.h>
#define LIMIT 500000

// modular exponentiation (a^d mod n) with 128-bit intermediate
long long modpow(long long a, long long d, long long n) {
    __uint128_t res = 1, base = a % n;
    while (d > 0) {
        if (d % 2) res = (res * base) % n;
        base = (base * base) % n;
        d /= 2;
    }
    return (long long)res;
}

int check_composite(long long n, long long a, long long d, int r) {
    long long x = modpow(a, d, n);
    if (x == 1 || x == n - 1) return 0;
    for (int i = 1; i < r; i++) {
        x = (__uint128_t) x * x % n;
        if (x == n - 1) return 0;
    }
    return 1;
}

// deterministic Miller–Rabin for 64-bit integers
int isPrime(long long n) {
    if (n < 2) return 0;
    long long small_primes[] = {2,3,5,7,11,13,17,19,23,0};
    for (int i = 0; small_primes[i]; i++) {
        if (n == small_primes[i]) return 1;
        if (n % small_primes[i] == 0) return 0;
    }

    // write n-1 = d * 2^r
    long long d = n - 1;
    int r = 0;
    while ((d % 2) == 0) {
        d /= 2;
        r++;
    }

    // deterministic bases for < 2^64
    long long bases[] = {2,325,9375,28178,450775,9780504,1795265022,0};
    for (int i = 0; bases[i]; i++) {
        long long a = bases[i] % n;
        if (a == 0) continue;
        if (check_composite(n, a, d, r)) return 0;
    }
    return 1;
}


int contains200(long n) {
    while (n>0) {
        if (n % 1000 == 200) break;
        n /= 10;
    }
    return !!n;
}

int primeProof(long n) {
    long p = 1;
    long m = n;
    int invalid = 0;
    while (m > 0) {
        int d = m%10;
        for (int i = 0; i<10; i++) {
            if (i == d) continue;
            if (isPrime(n+p*(i-d))) {
                invalid = 1;
                break;
            }
        }
        if (invalid) break;
        m /= 10;
        p *= 10;
    }
    return !invalid;
}

int cmp(const void *a, const void *b) {
    if (*(long *)a > *(long *)b) return 1;
    if (*(long *)a < *(long *)b) return -1;
    return 0;
}

int main(void) {
    unsigned char *IS_PRIME = malloc(sizeof(unsigned char) * LIMIT);
    long *primes = malloc(sizeof(long) * LIMIT);
    int numPrimes = 0;
    for (int p = 2; p<LIMIT; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<LIMIT; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    free(IS_PRIME);
    long solutions[800];
    int numSolutions = 0;
    for (int i = 0; i<numPrimes; i++) {
        for (int j = 0; j<numPrimes; j++) {
            if (i == j) continue;
            long long n = (long long) primes[i]*primes[i]*primes[j]*primes[j]*primes[j];
            if (n>1e12 || n<0) break;
            if (!contains200(n)) continue;
            if (!primeProof(n)) continue;
            solutions[numSolutions++] = n;
        }
    }
    qsort(solutions, numSolutions, sizeof(long), cmp);
    printf("%ld\n", solutions[199]);
    return 0;
}