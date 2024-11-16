//https://projecteuler.net/problem=70
//Totient Permutation

#include <stdio.h>
#include <math.h>
#define MAX 10000000

int IS_PRIME[MAX] = {0};
int primes[2097152];
int numPrimes;

void sieve() {
    numPrimes = 0;
    for (int i = 2; i<= MAX; i++)
    {
        if (!IS_PRIME[i]) {
            for (int j = 2; i * j<= MAX; j++)
                IS_PRIME[i * j]= 1;
        }
    }

    for (int i = 2; i<MAX;i++) {
        if (!IS_PRIME[i]) {
            primes[numPrimes] = i;
            numPrimes++;
        }
    }
}

int phi(int n) {
    int p = n;
    for (int i = 0; primes[i]*primes[i] <= n; i++) {
        if (n % primes[i]== 0) {
            p /= primes[i];
            p *= (primes[i] - 1);
 
            while (n % primes[i]== 0)
               n /= primes[i];
        }
    }

    if (n>1) {
        p -= p/n;
    }

 
    return p;
}

int main(void) {
    sieve();
    double min = 10000;
    int min_i = 0;
    for (int i = 2; i<MAX; i++) {
        int p = phi(i);
        int s = p;
        int q = i;
        int freq1[10] = {0};
        int freq2[10] = {0};
        while (p != 0) {
            freq1[p % 10]++;
            p /= 10;
        }
        while (q != 0) {
            freq2[q % 10]++;
            q /= 10;
        }

        int equal = 1;

        for (int j = 0; j<10; j++) {
            if (freq1[j] != freq2[j]) {
                equal = 0;
                break;
            }
        }
        
        if (equal && (double)i / s < min) {
            min = (double) i / s;
            min_i = i;
        }
    }
    printf("%d\n", min_i);
    return 0;
}