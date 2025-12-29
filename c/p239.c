//https://projecteuler.net/problem=239
//Twenty-two Foolish Primes

#include <stdio.h>

long long C(n,r) {
    // binomial coefficient nCr (n choose r) n!/r!(n-r)!
    int done[50] = {0};
    long long v = 1;
    for (int i = n-r+1; i<=n; i++) {
        v *= (long long) i;
        for (int j = 1; j<=r; j++) {
            if (!done[j] && v % j == 0) {
                v /= (long long) j;
                done[j]=1;
            }
        }
    }
    return v;
}

int main(void) {
    //because of symmetry, the prime numbers themselves do not matter. We know that there are 25 primes from
    //1 to 100, so we just need to find the probability that exactly 3 out of the 25 are in their right place
    //the number of ways of choosing these three are 25C3 so the initial number of ways in which these three
    //can be chosen is just 25C3 = 2300. Now we need to multiply this by the number of ways in which the rest
    //97 of the numbers can be arranged such that atleast 22 of them do not retain their original positions.
    //this can be counted using inclusion exclusion as the sum from k=0 to 22 of (-1)^k * 22Ck * (97-k)!
    //we have to divide this total count by the total number of permutations 100! to get our result.
    long sum = 0;
    int sign = 1;
    long double p = 0;
    for (int k = 0; k<=22; k++) {
        long double v = (long double) sign * C(22,k);
        for (int i = 97-k+1; i<=99; i++) {
            v /= (long double) i;
        }
        p += v;
        sign = -sign;
    }
    printf("%.12Lf\n", 23*p);
    return 0;
}