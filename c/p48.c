//https://projecteuler.net/problem=48
//Self Powers

#include <stdio.h>

long nexp(int n, long m) {
    //n**n mod m
    long k = 1;
    for (int i = 0; i<n; i++) {
        k = (long) (k*n) % m;
    }
    return k;
}

int main(void) {
    long S = 0;
    for (int i = 1; i<=1000; i++) {
        S += nexp(i,10000000000);
    }
    printf("%li\n",S%10000000000);
    return 0;
}