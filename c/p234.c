//https://projecteuler.net/problem=234
//Semidivisible Numbers

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 999966663333

long divsum(long a, long b, long n) {
    //returns sum of integers from a to b inclusive divisible by n.
    a = a%n == 0 ? a : a - a%n + n;
    b -= b%n;
    if (a>b) return 0;
    return ((b-a)/n+1)*(a+b)/2;
}

int main(void) {
    //we can loop over the possible values of sqrt(n) and group numbers that way to make it more efficient
    int s = sqrt(N);
    unsigned char *IS_PRIME = calloc(s+101, sizeof(unsigned char));
    int *primes = calloc(2.2*(double) s/log(N), sizeof(int));
    int numPrimes = 0;
    for (int p = 2; p<=s+100; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<=s+100; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    int l = 0;
    int r = 0;
    long ans = 0;
    for (int sqrtn = 2; sqrtn <= s; sqrtn++) {
        if (sqrtn >= primes[r]) r++;
        if (primes[l+1] <= sqrtn) l++;
        long a = (long) sqrtn*sqrtn;
        long b = (long) sqrtn*(sqrtn+2);
        if (b > N) b = N;
        long s = (divsum(a,b, primes[l]) + divsum(a,b, primes[r]) - 2*divsum(a,b,(long) primes[l]*primes[r]));
        if (sqrtn == primes[l]) s -= (long) sqrtn*sqrtn;
        ans += s;
    }
    printf("%ld\n", ans);
    free(IS_PRIME);
    free(primes);
    return 0;
}