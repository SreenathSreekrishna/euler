//https://projecteuler.net/problem=27
//Quadratic Primes

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

int getConsecutivePrimes(int a, int b) {
    //returns a value specifying the number of consecutive primes produced by the quadratic n^2+an+b starting from n=0
    int i = 0;
    while (isPrime((a+i)*i + b)) {
        i++;
    }
    return i;
}

int main(void) {
    int max = -1;
    int maxVal = -1;
    for (int a = -999; a<1000; a++) {
        for (int b = -1000; b<=1000; b++) {
            int v = getConsecutivePrimes(a,b);
            if (v > max) {
                max = v;
                maxVal = a*b;
            }
        }
    }
    printf("%d\n", maxVal);
    return 0;
}