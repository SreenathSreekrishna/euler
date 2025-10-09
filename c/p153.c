//https://projecteuler.net/problem=153
//Investigating Gaussian Integers

#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef __int128 i128;
#define N 100000000LL

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

i128 sumdiv(long long n) {
    //sum of sum of divisors from 1 to n
    //this is equivalent to sum of d*floor(n/d)
    //solved in O(sqrt(n)) using grouping
    i128 res = 0;
    long long i = 1;
    while (i <= n) {
        long long v = n / i;
        long long last = n / v;
        i128 cnt = (i128)(last - i + 1);
        i128 sum_d = (i128)(i + last) * cnt / 2;
        res += (i128)v * sum_d;
        i = last + 1;
    }
    return res;
}

int main(void) {
    i128 ans = 0;

    //sum of only integer divisors (no complex part)
    ans += sumdiv(N);

    //sum of gaussian divisors
    long long maxx = (long long)floor(sqrt(N));
    for (long long x = 1; x <= maxx; ++x) {
        long long maxy = (long long)floor(sqrt((long double)(N - x*x)));
        for (long long y = 1; y <= maxy; ++y) {
            if (gcd(x, y) != 1) continue;
            long long q = x*x + y*y;
            if (q > N) continue;
            long long m = N / q;
            if (m == 0) continue;
            i128 s = sumdiv(m);
            ans += (i128)2 * (i128)x * s;
        }
    }

    printf("%lld\n", (long long) ans);
    return 0;
}