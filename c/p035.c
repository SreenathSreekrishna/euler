//https://projecteuler.net/problem=35
//Circular Primes

#include <stdio.h>
#include <math.h>

int isPrime(int num) {
    if (num < 2) {
        return 0;
    }
    if (num == 2 || num == 3) {
        return 1;
    }
    for (int i = 2; i<=(sqrt(num)+1); i++) {
        if (num % i == 0) {
            return 0;
            break;
        }
    }
    return 1;
}

int shift(int n) {
    int k = pow(10, (int) log10(n));
    return k * (n % 10) + n / 10;
}

int main(void) {
    int s = 0;
    for (int i = 0; i<1000000; i++) {
        if (!isPrime(i)) {
            continue;
        }
        int allPrime = 1;
        for (int m = shift(i); m!=i; m=shift(m)) {
            if (!isPrime(m)) {
                allPrime = 0;
                break;
            }
        }
        if (allPrime) {
            s++;
        }
    }
    printf("%d\n", s);
    return 0;
}