//https://projecteuler.net/problem=256
//Tatami-Free Rooms

#include <stdio.h>
#include <stdlib.h>

long long ceildiv(long long a, long long b) {
    return a/b + !!(a%b);
}

long extendedGCD(long a, long b, long *x, long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long x1, y1;
    long g = extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

long modInverse(long a, long m) {
    long x, y;
    long g = extendedGCD(a, m, &x, &y);
    if (g != 1) {
        return -1;
    }
    long res = (x % m + m) % m;
    return res;
}

int tatami_possible(long long a, long long b){
    if (a > b) {
        long long t = a;
        a = b;
        b = t;
    }

    if (a % 2 == 1) {
        if (b % 2 == 1) return 0;
        long long n = b / 2;
        long long ap = (a-1) / 2;
        long long bp = (a+1) / 2;
        long long g = ap*bp - ap - bp;
        if (n > g) return 1;
        long long inv = modInverse(ap, bp);
        if (inv == -1) return 0;
        long long x0 = ((n % bp) * inv) % bp;
        return ap*x0 <= n;
    }

    for (int d = -1; d <= 1; d++) {
        long long sd = b - d;
        if (sd < 0) continue;
        long long den1 = a + 1;
        long long den2 = a - 1;
        long long kmin = ceildiv(sd, den1);
        if (kmin < 0) kmin = 0;
        long long kmax = sd / den2;
        if (kmax < 0) continue;
        if (kmin > kmax) continue;
        for (long long k = kmin; k <= kmax; k++) {
            long long m = k + d;
            if (m < 0) continue;
            long long base = k * (a - 1);
            if (sd < base) continue;
            long long rem = sd - base;
            if (rem > 2*k) continue;
            if (rem % 2) continue;
            return 1;
        }
    }
    return 0;
}

int main(void){
    int LIMIT = 100000000;
    int *numdivs = calloc(LIMIT+1, sizeof(int));
    for (int n = 1; n<=LIMIT; n++) {
        for (int i = 0; i<=LIMIT; i+=n) numdivs[i] ++;
    }
    int n;
    for (n = 1; n<=LIMIT; n++) {
        if (numdivs[n] < 400) continue;
        int T = 0;
        for (int i = 1; i*i <= n; i++)
            if (n%i == 0) T += !tatami_possible(i, n/i);
        if (T == 200) break;
    }
    printf("%d\n", n);
    free(numdivs);
    return 0;
}