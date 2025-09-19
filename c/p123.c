//https://projecteuler.net/problem=123
//Prime Square Remainders

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    for (int i = 2; i<sqrt(n)+1; i++) if (n % i == 0) return 0;
    return 1;
}

long f(long p, int n) {
    long a = 1;
    long b = 1;
    long s = p*p;
    for (int i = 0; i<n; i++) {
        a = a*(p-1) % s;
        b = b*(p+1) % s;
    }
    return (a+b)%s;
}

int main(void) {
    //same as p120
    int n = 0;
    long p = 1;
    while (1) {
        p++;
        if (!isPrime(p)) continue;
        n ++;
        if (f(p,n) > 10000000000) {
            break;
        }
    }
    printf("%d\n", n);
    return 0;
}