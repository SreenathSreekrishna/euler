//https://projecteuler.net/problem=69
//Totient Maximum

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
    //we will use the fact that phi(n)=n(1-1/p1)(1-1/p2)...,
    //where p1,p2,p3... are the primes in the factorization of n
    //n/phi(n) will be maximum when (p1p2p3p4...)/((p1-1)(p2-1)(p3-1)...) is maximum
    //notice that this maximum is achieved when n is composed of only
    //consecutive primes for example 30, for which n/phi(n)=3.75; which is the
    //maximum upto 30
    double v = 1;
    int n = 1;
    int i = 2;
    while (n<1000000) {
        if (!isPrime(i)) {
            i++;
            continue;
        }
        n *= i;
        v *= i;
        v /= (i-1);
        i++;
    }

    printf("%d\n", n/(i-1));
    return 0;
}