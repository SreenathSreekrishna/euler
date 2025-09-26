//https://projecteuler.net/problem=140
//Modified Fibonacci Golden Nuggets

#include <stdio.h>

int main(void) {
    //generating function of A_G comes out to (3x^2+x)/(1-x-x^2)
    //if (3x^2+x)/(1-x-x^2) = n has rational roots, the discriminant of the quadratic is a square
    //(n+3)x^2+(n+1)x-n=0; 5n^2+14n+1 is a perfect square
    //(5n+7)^2 - 5k^2 = 44
    //m^2 - 5k^2 = 44
    //notice that the unit of a^2 - 5b^2 (Z[sqrt(5)]) is 9+4*sqrt(5)
    //thus, the problem is reduced to finding all fundamental solutions which are different even upto 
    //multiplication by the unit, and then multiply all of them by powers of the unit to find all solutions
    //by bruteforce calculation, we get the fundamentals and then just do the same recursive sequence
    long long m[6] = {7,8,13,17,32,43};
    long long k[6] = {1,2,5,7,14,19};
    long long sum = 0;
    int num = 0;
    while (num<30) {
        for (int i = 0; i<6; i++) {
            if (m[i] % 5 == 2 && m[i]>7) {
                sum += (m[i]-7)/5;
                num++;
            }
            if (num >= 30) break;
            long long tmp = m[i];
            m[i] = 9*m[i]+20*k[i];
            k[i] = 4*tmp +9*k[i];
        }
    }
    printf("%lld\n", sum);
    return 0;
}