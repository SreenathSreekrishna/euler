//https://projecteuler.net/problem=243
//Resilience

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000000000
#define P 15499L
#define Q 94744L

int primes[50] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229};
long min = __LONG_MAX__;

void dfs(long n, long phi, int lastPrimeIndex) {
    if (n > MAX) return;
    if (lastPrimeIndex >= 50) return;
    if (n < min && Q*phi < P*(n-1)) min = n;
    if (lastPrimeIndex >= 0)
        dfs(n*primes[lastPrimeIndex], phi*primes[lastPrimeIndex], lastPrimeIndex);
    for (int i = lastPrimeIndex+1; i<50; i++)
        dfs(n*primes[i], phi*(primes[i]-1), i);
} 

int main(void) {
    //it is obvious that R(n) = phi(n)/(n-1).
    //for R(n) < P/Q, phi(n) < P(n-1)/Q
    dfs(1, 1, -1);
    printf("%ld\n", min);
    return 0;
}