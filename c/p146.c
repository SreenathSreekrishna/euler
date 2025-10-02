//https://projecteuler.net/problem=146
//Investigating a Prime Pattern

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define LIMIT 150000000

int nums[6] = {1,3,7,9,13,27};

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

long extended_gcd(long a, long b, long *x, long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long x1, y1;
    long g = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

long mod_inverse(long a, long m) {
    long x, y;
    long g = extended_gcd(a, m, &x, &y);
    if (g != 1) {
        return -1;
    }
    long res = (x % m + m) % m;
    return res;
}

long crt(long x1, long x2, long p, long q) {
    long inv_p_mod_q = mod_inverse(p, q);
    long t = ((x2 - x1) % q + q) % q;
    t = ((1LL * t * inv_p_mod_q) % q);
    long a = x1 + p * t;
    return (a % (p * q) + p * q) % (p * q);
}

int works(int n) {
    return isPrime((long) n*n + 1) && isPrime((long) n*n + 3)
        && isPrime((long) n*n + 7) && isPrime((long) n*n + 9)
        && !isPrime((long) n*n + 11) && isPrime((long) n*n + 13)
        && !isPrime((long) n*n + 17) && !isPrime((long) n*n + 19)
        && !isPrime((long) n*n + 21) && !isPrime((long) n*n + 23)
        && isPrime((long) n*n + 27);
}

int addPossibilities(int possibilities[], int numPossibilities, int p, int product) {
    //take all possibilities for n mod product of primes<p, and use CRT to find possibilities
    //for n mod product of primes upto including p
    //The possibilities mod p are just all n<p such that n^2 != -1,-3,-7,-9,-13,-27 mod p 
    int newPoss[1024];
    int numNewPoss = 0;
    for (int i = 0; i<p; i++) {
        int failed = 0;
        for (int j = 0; j<6; j++) {
            if ((i*i+nums[j])%p == 0) {
                failed = 1;
                break;
            }
        }
        if (failed) continue;
        newPoss[numNewPoss] = i;
        numNewPoss++;
    }
    for (int i = 0; i<numPossibilities; i++)
    for (int j = 0; j<numNewPoss; j++)
        possibilities[numPossibilities*j+i] = crt(newPoss[j],possibilities[i],p,product);
    return numPossibilities*numNewPoss;
}

int main(void) {
    //Solve by first filtering using CRT then miller-rabin

    int prod = 1;
    unsigned char IS_PRIME[2048] = {0};
    int *possibilities = malloc(sizeof(int)*LIMIT);
    possibilities[0] = 0;
    int numPossibilities = 1;
    for (int p = 2; prod<LIMIT; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<2048; j++)
                IS_PRIME[p * j]= 1;
            numPossibilities = addPossibilities(possibilities,numPossibilities,p, prod);
            prod*=p;
        }
    }

    long sum = 0;
    for (int i = 0; i<numPossibilities; i++) {
        if (possibilities[i] > LIMIT) continue;
        if (works(possibilities[i])) sum += possibilities[i];
    }
    printf("%ld\n", sum);
    free(possibilities);
    return 0;
}