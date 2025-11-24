//https://projecteuler.net/problem=202
//Laserbeam

#include <stdio.h>
#define N 12017639147

long mu(long n) {
    //mobius function mu(n).
    if (n == 1) return 1;
    int ret = 1;
    while (n > 1) {
        for (int i = 2; i<=n; i++) {
            int num = 0;
            while (n%i == 0) {
                num++;
                n /= i;
            }
            if (num >= 2) return 0;
            if (num == 1) ret *= (-1);
        }
    }
    return ret;
}

long numDiv(long k, long n) {
    //number of x = 2 mod 3 in 1...k divisible by n.
    if (n%3 == 0) return 0;
    long ret = (k - (3 - n%3)*n)/(3*n) + 1;
    if (ret<0) ret = 0;
    return ret;
}

int main(void) {
    //using math and some observation, i found that the number of ways a laser beam can bounce in the
    //manner specified is just equivalent to the number of (x,y) ordered pairs of positive integers such
    //that x=2 mod 3; gcd(x,y) = 1 and 2(x+y)-3=N. => y = (N+3)/2 - x; => gcd(x,(N+3)/2) = 1; x=2 mod 3.
    //the condition x=2 mod 3 is imposed because the laser must exit from the same hole it started from.
    //now, we just use inclusion exclusion (mobius inversion) with the divisors of k to find number of x 
    //coprime to k with conditions satisfied.
    long k = (N+3)/2;
    long ans = (k+1)/3;
    for (long i = 2; i*i<=k; i++) {
        if (k%i) continue;
        ans += mu(i)*numDiv(k,i);
        ans += mu(k/i)*numDiv(k,k/i);
    }
    printf("%ld\n", ans);
    return 0;
}