//https://projecteuler.net/problem=3
//Largest prime factor

#include <stdio.h>

int  getSmallestPrimeFactor(int n) {
    int i = 2;
    while (1) {
        if (n % i == 0) {
            return i;
        }
        i+=1;
    }
}

int main(void) {
    int f;
    long n = 600851475143;
    while (n != 1) {
        f = getSmallestPrimeFactor(n);
        n /= f;
    }
    printf("%d\n", f);
}