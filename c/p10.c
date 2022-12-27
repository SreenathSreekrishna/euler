//https://projecteuler.net/problem=10
//Summation of primes

#include <stdio.h>
#include <math.h>

int main(void) {
    long sum = 0;
    int n = 2000000;
    for (int i = 2; i<n; i++) {
        int isPrime = 1;
        for (int j = 2; j<=sqrt(i); j++) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime) {
            sum += i;
        }
    }
    printf("%li\n", sum);
    return 0;
}