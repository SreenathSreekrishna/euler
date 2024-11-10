//https://projecteuler.net/problem=37
//Truncatable Primes

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

int truncatablePrimeLeft(int n) {
    //returns a value telling if a prime is truncatable from the left
    if (!isPrime(n)) {
        return 0;
    }
    int p = pow(10, (int) log10(n));
    int v = n % p;
    if (v == 0) {
        return 1;
    }
    return truncatablePrimeLeft(v);
}

int truncatablePrimeRight(int n) {
    //returns a value telling if a prime is truncatable from the right
    if (!isPrime(n)) {
        return 0;
    }
    int v = n / 10;
    if (v == 0) {
        return 1;
    }
    return truncatablePrimeRight(v);
}

int main(void) {
    int numTrunc = 11; //total number of truncatable primes is given as 11 on the problem page
    int i = 10;
    int s = 0;
    while (numTrunc > 0) {
        if (!truncatablePrimeLeft(i)) {
            i++;
            continue;
        }
        if (!truncatablePrimeRight(i)) {
            i++;
            continue;
        }
        s += i;
        numTrunc--;
        i++;
    }
    printf("%d\n", s);
    return 0;
}