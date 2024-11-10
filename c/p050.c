//https://projecteuler.net/problem=50
//Consecutive Prime Sum

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n <= 3) {
        return 1;
    }
    for (int i = 2; i<sqrt((float) n)+1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int primes[50000];
    int nPrimes = 0;

    for (int i = 0; i<500000; i++) {
        if (isPrime(i)) {
            primes[nPrimes] = i;
            nPrimes++;
        }
    }

    long primeSum[nPrimes+1];
    primeSum[0] = 0;
    long sum = 0;

    for (int i = 0; i<nPrimes; i++) {
        sum += primes[i];
        primeSum[i+1] = sum;
    }

    int m = 0;
    int m_p = 0;

    for (int start = 0; start<nPrimes-1; start++) {
        for (int end = start+1; end<nPrimes; end++) {
            long s = primeSum[end+1] - primeSum[start];
            int r = end - start + 1;
            if (s < 1000000) {
                if (isPrime(s)) {
                    if (r > m) {
                        m = r;
                        m_p = s;
                    }
                }
            }
        }
    }

    printf("%d\n",m_p);
    return 0;
}