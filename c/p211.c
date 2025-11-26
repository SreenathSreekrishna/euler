//https://projecteuler.net/problem=211
//Divisor Square Sum

#include <stdio.h>
#include <math.h>
#define N 64000000

long long sigma2[N] = {0};

long long sqrti(long long x) {
    //integer sqrt function that adjusts sqrtl that is sometimes a little off.
    //i found this to be much more efficient than doing a pure integer binsrch sqrt.
    if (x <= 0) return 0;
    long long r = sqrtl((long double) x);
    while (r * r > x) r--;
    return r;
}

int main(void) {
    //i just loop over all multiples using a usual sieve method like how i do number of factors in a range.
    for (long i = 1; i<N; i++) {
        for (long j = i; j<N; j+=i) {
            sigma2[j] += i*i;
        }
    }
    long long ans = 0;
    for (long i = 1; i<N; i++) {
        long long s = sqrti(sigma2[i]);
        if (s*s == sigma2[i]) ans += i;
    }
    printf("%lld\n", ans);
    return 0;
}