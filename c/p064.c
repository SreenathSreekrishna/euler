//https://projecteuler.net/problem=64
//Odd Period Square Roots

#include <stdio.h>
#include <math.h>

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

int sqrtPeriod(int n) {
    int prevStates[10000][4];
    int a[10000] = {0};
    int p = 1;
    int q = 0;
    int r = 1;
    for (int i = 0; i<10000; i++) {
        a[i] = (int) (((float) sqrt(n)*p + q) / r);
        int p1 = r*p;
        int q1 = r*r*a[i]-r*q;
        int r1 = p*p*n-q*q+2*a[i]*q*r-a[i]*a[i]*r*r;
        int g = gcd(gcd(p1,q1),r1);
        p = p1 / g;
        q = q1 / g;
        r = r1 / g;
        int l[4] = {a[i],p,q,r};
        for (int j = 0; j<i; j++) {
            int fail = 1;
            for (int k = 0; k<4; k++) {
                if (prevStates[j][k] != l[k]) {
                    fail = 0;
                    break;
                }
            }
            if (fail) {
                return i-1;
            }
        }
        for (int j = 0; j<4; j++) {
            prevStates[i][j] = l[j];
        }
    }
    return -1;
}

int main(void) {
    int c = 0;
    for (int i = 1; i<=10000; i++) c += (sqrtPeriod(i) % 2);
    printf("%d\n",c);
    return 0;
}