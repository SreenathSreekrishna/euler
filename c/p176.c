//https://projecteuler.net/problem=176
//Common Cathetus Right-angled Triangles

#include <stdio.h>
#define M 47547

int main(void) {
    //Let the cathetus be N. In that case, N^2 = c^2 - b^2 for some integers c>b.
    // => N^2 = (c-b)(c+b)
    //The solutions to this are pretty well known. (just the count of factors of same of same parity)
    //If N odd, M = (d(N^2)-1) / 2; if N even, M = (d(N^2 / 4) - 1)/2 (d(N) is # of divisors of N)
    //We dont want N odd as then the least prime would be 3 which would become too big.
    //Thus we only consider N even. => 2*M+1 = d(N^2 / 4)
    //this means the exponents are just 1 less than the prime factorization of 2*M+1.
    //We order the prime factors of 2*M+1 in decreasing order and assign the largest exponent to least
    //prime (3) and so on.
    int primes[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53}; //can write sieve but meh whatever
    int primeFactors[16];
    int numFactors = 0;
    int v = 2*M+1;
    while (v>1) {
        for (int i = 2; i<=v; i++) {
            while (v % i == 0) {
                v /= i;
                primeFactors[numFactors++] = i;
            }
        }
    }
    long long ans = 2;
    for (int i = numFactors-1; i>=0; i--)
    for (int j = 0; j<(primeFactors[i]-1)/2; j++)
        ans *= primes[numFactors-i-1];
    printf("%lld\n", ans);
    return 0;
}