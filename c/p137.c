//https://projecteuler.net/problem=137
//Fibonacci Golden Nuggets

#include <stdio.h>

int main(void) {
    //generating function of A_F comes out to x/(1-x-x^2)
    //if x/(1-x-x^2) = n has rational roots, the discriminant of the quadratic is a square
    //nx^2+(n+1)x-n=0; 5n^2+2n+1 is a perfect square
    //5k^2 - (5n+1)^2 = 4
    //next we just find the recursive sequence for this using continued fractions
    long long k = 1;
    long long n = 0;
    for (int i = 0; i<15; i++) {
        long long tmp = k;
        k = (7*k+15*n+3)/2;
        n = (3*tmp+7*n+1)/2;
    }
    printf("%lld\n",n);
    return 0;
}