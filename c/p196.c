//https://projecteuler.net/problem=196
//Prime Triplets

#include <stdio.h>
#include <stdlib.h>
#define A 5678027
#define B 7208785

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

long S(int n) {
    unsigned char *prevprev = calloc(n+2, sizeof(unsigned char));
    unsigned char *prev = calloc(n+2, sizeof(unsigned char));
    unsigned char *curr = calloc(n+2, sizeof(unsigned char));
    unsigned char *next = calloc(n+2, sizeof(unsigned char));
    unsigned char *nextnext = calloc(n+2, sizeof(unsigned char));
    long start = (long) (n-2)*(n-3) / 2;
    for (long i = 0; i<n-2; i++) prevprev[i] = isPrime(start+i+1);
    for (long i = 0; i<n-1; i++) prev[i] = isPrime(start+i+n-1);
    for (long i = 0; i<n; i++) curr[i] = isPrime(start+i+2*n-2);
    for (long i = 0; i<n+1; i++) next[i] = isPrime(start+i+3*n-2);
    for (long i = 0; i<n+2; i++) nextnext[i] = isPrime(start+i+4*n-1);
    unsigned char *part = calloc(n+2, sizeof(unsigned char));
    for (int i = 0; i<n-1; i++) {
        if (!prev[i]) continue;
        int v = (i ? prevprev[i-1]+prev[i-1]+curr[i-1] : 0) + prevprev[i] + prevprev[i+1] 
        + prev[i] + prev[i+1] + curr[i] + curr[i+1];
        if (v < 3) continue;
        if (i) part[i-1] = curr[i-1];
        part[i] = curr[i];
        part[i+1] = curr[i+1];
    }
    for (int i = 0; i<n; i++) {
        if (!curr[i]) continue;
        int v = (i ? prev[i-1]+curr[i-1]+next[i-1] : 0) + prev[i] + prev[i+1] 
        + curr[i] + curr[i+1] + next[i] + next[i+1];
        if (v < 3) continue;
        if (i) part[i-1] = curr[i-1];
        part[i] = curr[i];
        part[i+1] = curr[i+1];
    }
    for (int i = 0; i<n+1; i++) {
        if (!next[i]) continue;
        int v = (i ? curr[i-1]+next[i-1]+nextnext[i-1] : 0) + curr[i] + curr[i+1] 
        + next[i] + next[i+1] + nextnext[i] + nextnext[i+1];
        if (v < 3) continue;
        if (i) part[i-1] = curr[i-1];
        part[i] = curr[i];
        part[i+1] = curr[i+1];
    }
    long ret = 0;
    for (int i = 0; i<n+2; i++) if (part[i]) ret += (start+i+2*n-2);
    free(prevprev); free(prev); free(curr); free(next); free(nextnext); free(part);
    return ret;
}

int main(void) {
    printf("%ld\n", S(A)+S(B));
    return 0;
}