//https://projecteuler.net/problem=73
//Counting Fractions in a Range

#include <stdio.h>

int gcd(int a, int b) {
    if (a == b) {
        return a;
    }
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    if (b>a) {
        return gcd(a,b % a);
    }
    if (a>b) {
        return gcd(b,a % b);
    }
    return 1;
}

int compare(int a1, int b1, int a2, int b2) {
    //returns if a1/b1>a2/b2
    return a1*b2 > a2*b1;
}

int main(void) {
    int s = 0;
    for (int d = 2; d<=12000; d++) {
        for (int n = 1; n<d; n++) {
            if (gcd(n,d) != 1) {
                continue;
            }
            s += (compare(n,d,1,3) && compare(1,2,n,d));
        }
    }
    printf("%d\n", s);
}