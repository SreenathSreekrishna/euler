//https://projecteuler.net/problem=47
//Distinct Primes Factors

#include <stdio.h>

int distinctPrimeFactors(int n) {
    int num = 0;
    int prevPrime = -1;
    while (n != 1) {
        int i = 2;
        while (n%i != 0) {
            i++;
        }
        n /= i;
        if (i != prevPrime) num++;
        prevPrime = i;
    }
    return num;
}

int main(void) {
    int n = 2;
    int d[4] = {1,1,1,1};
    while (d[0]!=4 || d[1]!=4 || d[2]!=4 || d[3]!=4) {
        n++;
        d[0] = d[1];
        d[1] = d[2];
        d[2] = d[3];
        d[3] = distinctPrimeFactors(n+3);
    }
    printf("%d\n",n);
    return 0;
}