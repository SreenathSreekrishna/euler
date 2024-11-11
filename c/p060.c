//https://projecteuler.net/problem=60
//Prime Pair Sets

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

int concatPrime(int a, int b) {
    int k = b;
    int numDigits = 0;
    int p = 1;
    while (k != 0) {
        k /= 10;
        p *= 10;
    }
    return isPrime(a*p + b);
}

int main(void) {
    int primes[2048];
    int numPrimes = 0;
    for (int i = 0; i<10000; i++) {
        if (isPrime(i)) {
            primes[numPrimes] = i;
            numPrimes++;
        }
    }

    for (int i = 0; i<numPrimes; i++) {
        for (int j = i+1; j<numPrimes; j++) {
            if (!concatPrime(primes[i],primes[j] || !concatPrime(primes[i],primes[j]))) {
                continue;
            }
            for (int k = j+1; k<numPrimes; k++) {
                if (!concatPrime(primes[i],primes[k]) || !concatPrime(primes[k],primes[i])
                 || !concatPrime(primes[j],primes[k]) || !concatPrime(primes[k],primes[j])) {
                    continue;
                }
                for (int l = k+1; l<numPrimes; l++) {
                    if (!concatPrime(primes[i],primes[l]) || !concatPrime(primes[l],primes[i])
                     || !concatPrime(primes[j],primes[l]) || !concatPrime(primes[l],primes[j])
                     || !concatPrime(primes[k],primes[l]) || !concatPrime(primes[l],primes[k])) {
                        continue;
                    }
                    for (int m = l+1; m<numPrimes; m++) {
                        if (concatPrime(primes[i],primes[m]) && concatPrime(primes[m],primes[i])
                         && concatPrime(primes[j],primes[m]) && concatPrime(primes[m],primes[j])
                         && concatPrime(primes[k],primes[m]) && concatPrime(primes[m],primes[k])
                         && concatPrime(primes[l],primes[m]) && concatPrime(primes[m],primes[l])) {
                            printf("%d\n",primes[i]+primes[j]+primes[k]+primes[l]+primes[m]);
                            return 0;
                        }
                    }
                }
            }
        }
    }

}