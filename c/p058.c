//https://projecteuler.net/problem=58
//Spiral Primes

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
    //notice that all diagonals on this spiral are of the form
    //x^2, x^2-x+1, x^2-2x+2, x^2-3x+3; where x is an odd number
    //from 1 to n, where n is the side length of the square

    int primes = 0;
    int n = 3;
    do {
        for (int i = 0; i<4; i++) primes += (isPrime(n*n - i*n + i));
        n += 2;
    } while ((float) primes / (float) (2*n - 1) * 100 > 10);
    printf("%d\n",n);
}