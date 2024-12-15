//https://projecteuler.net/problem=100
//Arranged Probability

#include <stdio.h>

int main(void) {
    unsigned long long n = 1;
    unsigned long long b = 1;
    unsigned long long p = 1;
    unsigned long long q = 1;
    while (n<1000000000000) {
        unsigned long long tmp = p;
        p = 3*p + 2*q;
        q = 4*tmp + 3*q;
        b = (p+1) / 2;
        n = (q+1) / 2;
    }
    printf("%llu\n", b);
    return 0;
}