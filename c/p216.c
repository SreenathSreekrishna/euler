//https://projecteuler.net/problem=216
//The Primality of 2⁢n^2 − 1

#include <stdio.h>
#define N 50000000

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

int main(void) {
    int ans = 0;
    for (int i = 2; i<=N; i++) {
        if (i>20
            &&(i%7 == 2 || i%7 == 5 
            || i%17 == 3 || i%17 == 14 
            || i%23 == 9 || i%23 == 14
            || i%31 == 4 || i%31 == 27 
            || i%41 == 12 || i%41 == 29 
            || i%47 == 20 || i%47 == 27
            || i%71 == 6  || i%71 == 65
            || i%73 == 16 || i%73 == 57
            || i%79 == 35 || i%79 == 44
            || i%89 == 32 || i%89 == 57
            || i%97 == 7  || i%97 == 90
            || i%103 == 19|| i%103 == 84
            || i%113 == 31|| i%113 == 82
            || i%127 == 8 || i%127 == 119
            || i%137 == 53|| i%137 == 84
            || i%151 == 23|| i%151 == 128)) continue;
        ans += isPrime((long long) 2*i*i - 1);
    }
    printf("%d\n", ans);
    return 0;
}