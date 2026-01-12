//https://projecteuler.net/problem=245
//Coresilience

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#define SIEVE 500000
#define N 200000000000LL

long ans = 0;
int curr;
int *primes;
int numPrimes = 0;

long gcd(long a, long b) {
    long tmp;
    while(b) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

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

void dfs(long n, long phi, int idx) {
    if (gcd(n, phi) != 1) return;

    if (n > 1) {
        long lp = primes[idx + 1];
        long rp = N / n;
        long lb = (n*lp - 1) / ((n-phi)*lp + phi);
        long rb = (n*rp - 1) / ((n-phi)*rp + phi);
        lb += lb%2;

        for (long i = lb; i <= rb; i += 2){
            if (n == curr && (i*i - i + 1) % (n - i) != 0) continue;
            if (gcd(n, i) != 1) continue;
            long w = phi * i;
            long pv = modpow(w % n, phi - 1, n) + 1;
            for(long p = pv; p <= w + 1 && p <= N / n; p += n)
                if((w + 1) % p == 0 && p > primes[idx] && isPrime(p)) ans += n * p;
        }
    }

    while (idx < numPrimes) {
        int p = primes[idx];
        if(n > N / p / p) break;
        dfs(n * p, phi * (p - 1), idx);
        idx++;
    }
}

int main() {
    //i first noticed that n is never even and always was the product of distinct primes.
    //i thus just run a dfs with small primes and switch to miller rabin for larger primes
    //also added some optimizations because it was extremely slow.
    unsigned char *IS_PRIME = calloc(SIEVE+1, sizeof(unsigned char));
    primes = calloc(1.1*(double) SIEVE/log(SIEVE), sizeof(int));
    for (int p = 2; p<=SIEVE; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<=SIEVE; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    free(IS_PRIME);

    for (int i = 0; i<numPrimes; i++){
        long p = primes[i];
        if (p*p > N) break;
        curr = p;
        dfs(p, p-1, i);
    }
    printf("%ld\n", ans);
    free(primes);
    return 0;
}