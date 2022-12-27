//https://projecteuler.net/problem=12
//Highly divisible triangular number

#include <stdio.h>

int  getSmallestPrimeFactor(long n) {
    int i = 2;
    while (1) {
        if (n % i == 0) {
            return i;
        }
        i+=1;
    }
}

int numFactors(long n) {
    int prevFactor;
    int prevCount = 1;
    int cnt = 1;
    while (n != 1) {
        int k = getSmallestPrimeFactor(n);
        n /= k;
        if (prevFactor == k) {
            prevCount += 1;
        }
        else {
            cnt *= (prevCount+1);
            prevCount = 1;
        }
        prevFactor = k;
    }
    return cnt;
}

int main(void) {
    //formula for triangle numbers -> n*(n+1)/2
    int n = 500;
    long i = 1;
    long k;
    while (1) {
        k = i*(i+1)/2;
        int num = numFactors(k);
        if (num > n) {
            break;
        }
        i+=1;
    }
    printf("%li\n", k);
    return 0;
}