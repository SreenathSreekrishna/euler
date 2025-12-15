//https://projecteuler.net/problem=235
//An Arithmetic Geometric Sequence

#include <stdio.h>
#include <math.h>

long double f(long double r) {
    long double rpow = powl(r,5000);
    return 300.0f*(rpow-1)/(r-1) - (5000.0f*rpow*r - 5001.0*rpow + 1)/(r*r-2*r+1) + 2e11;
}

int main(void) {
    //u(k) = (900-3k)r^(k-1) = 900*r^(k-1) - 3k(r^(k-1))
    //s(n) = 900(r^n-1)/(r-1) - 3(1+2r+3r^2...+nr^(n-1))
    //s(n) = 900(r^n-1)/(r-1) - 3((r^n-1)/(r-1) + (r^n-r)/(r-1) ... (r^n-r^(n-1))/(r-1))
    //s(n) = 900(r^n-1)/(r-1) - 3(nr^n - (r^n-1)/(r-1))/(r-1)
    //s(n) = 900(r^n-1)/(r-1) - 3(nr^(n+1)-(n+1)r^n+1)/(r-1)^2
    //thus, s(5000) = -6*10^11 => 900(r^5000-1)/(r-1) - 3(5000r^5001-5001r^5000+1)/(r-1)^2 = -6*10^11
    // => set the expression to f(x) and exploit continuity using binsrch to solve.
    long double l = 0;
    long double r = 1.9;
    for (int i = 0; i<64; i++) {
        long double m = (l+r)/2.0;
        long double v = f(m);
        if (v > 0) l = m;
        else r = m;
    }
    printf("%.12Lf\n", l);
    return 0;
}