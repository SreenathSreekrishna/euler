//https://projecteuler.net/problem=46
//Goldbach's Other Conjecture

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

int sumPrimeSquare(int n) {
    int s = sqrt(n/2);
    while (!isPrime(n - 2*s*s)) {
        if (s == 0) {
            return 0;
        }
        s--;
    }
    return 1;
}

int main(void) {
    int n = 3;
    while (sumPrimeSquare(n)) {
        n+=2;
    }
    printf("%d\n",n);
    return 0;
}