//https://projecteuler.net/problem=233
//Lattice Points on a Circle

#include <stdio.h>
#include <stdlib.h>
#define BOUND 100000000000
#define N 420

int *primes;
int numPrimes = 0;
long long ans = 0;

void addPrimitive(long n, int last) {
    if (n > BOUND) return;
    ans += n;
    for (int i = last; i<numPrimes; i++) {
        if (primes[i] % 4 == 1) continue;
        long long v = n*primes[i];
        if (v > BOUND) return;
        addPrimitive(v, i);
    }
}

void generateAllPrimitives(int exponents[], int len, int idx, long n, int prev) {
    //gives all possible "primitive" numbers that have particular exponents
    //i call them "primitive" as they will only contain primes in their factorizations that are 1 mod 4.
    //we can multiply them by any other primes not 1 mod 4 to also preserve the property.
    if (idx == len) {
        addPrimitive(n, 0);
        return;
    }
    for (int i = prev+1; i<numPrimes; i++) {
        if (primes[i] % 4 != 1) continue;
        long long new = n;
        for (int j = 0; j<exponents[idx]; j++) {
            new *= primes[i];
            if (new > BOUND) return;
        }
        generateAllPrimitives(exponents, len, idx+1, new,i);
    }
}

void getFactorizations(int fac[], int n, int idx) {
    //gets all factorizations of the exponents of the 4k+1 primes.
    if (n == 1) {
        int exponents[100];
        for (int i = 0; i<idx; i++) exponents[i] = (fac[i] - 1) / 2;
        generateAllPrimitives(exponents,idx,0,1,0);
        return;
    }
    for (int i = 3; i<=n; i+=2) {
        if (n%i) continue;
        fac[idx] = i;
        getFactorizations(fac, n/i, idx+1);
    }
}

int main(void) {
    //if n=2k, f(2k) = # of (x,y) : x^2 + y^2 = 2k^2 = (n^2)/2
    //if n=2k+1, f(2k+1) = # of (x,y) : (2x+1)^2 + (2y+1)^2 = 2(2k+1)^2
    //thus it can be proven that f(n) = # of (x,y) : x^2 + y^2 = n^2 if n odd
    //number of solutions for x^2+y^2 = m for unrestricted x,y is just 4(e1+1)(e2+1)...
    //where e1,e2... are the exponents in the primes 1 mod 4 in the prime factorization of m.
    //thus in the example, to find f(10^4), m=n^2/2 (n even), so m=5*10^7=2^7 * 5^8.
    //notice that even when n even, n^2/2 has the same number of representations as n^2.
    //thus the problem is now just finding all n such that n^2 has N representations.
    //thus f(10^4) = 4(8+1) = 36.
    unsigned char *IS_PRIME = calloc(10000001, sizeof(unsigned char));
    primes = calloc(2048, sizeof(int));
    numPrimes = 0;
    for (int p = 2; p<=10000000; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<=10000000; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    free(IS_PRIME);
    int fac[100];
    getFactorizations(fac, N/4, 0);
    printf("%lld\n", ans);
    free(primes);
    return 0;
}