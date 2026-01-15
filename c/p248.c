//https://projecteuler.net/problem=248
//Euler's Totient Function Equals 13!

#include <stdio.h>
#include <stdlib.h>
#define N 6227020800

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

int cmp(const void *a, const void *b) {
    long x = *(long *)a, y = *(long *)b;
    if (x>y) return 1;
    if (x<y) return -1;
    return 0;
}

long primes[1000];
int numPrimes = 0;
long answers[200000];
int numAnswers = 0;

void dfs(long n, int lastUsed, long left) {
    //1) use lastprime again
    //2) use different prime
    if (left == 1) {
        answers[numAnswers++] = n;
        return;
    }
    if (lastUsed != -1 && left % primes[lastUsed] == 0)
        dfs(n*primes[lastUsed], lastUsed, left/primes[lastUsed]);
    for (int i = lastUsed+1; i<numPrimes; i++) {
        long p = primes[i];
        if (left % (p-1)) continue;
        dfs(n*p, i, left/(p-1));
    }
}

int main(void) {
    //13! = 2^10 * 3^5 * 5^2 * 7 * 11 * 13
    //if p | n, then p-1 | phi(n) => p-1 | 13!
    //we first list all divisors of 13!, add one to each and check primality.
    //each of the ones which are prime are candidates to be a part of the factorization
    //of n.
    for (long d = 1; d*d <= N; d++) {
        if (N % d) continue;
        if (isPrime(d+1)) primes[numPrimes++] = d+1;
        if (isPrime(N/d+1)) primes[numPrimes++] = N/d+1;
    }
    dfs(1, -1, N);
    qsort(answers, numAnswers, sizeof(long), cmp);
    printf("%ld\n", answers[149999]);
    return 0;
}