//https://projecteuler.net/problem=157
//Base-10 Diophantine Reciprocal

#include <stdio.h>
#include <math.h>

long gcd(long a, long b) {
    if (!b) return a;
    return gcd(b,a%b);
}

int d(long n) {
    int ret = 1;
    while (n>1) {
        for (int i = 2; i<=n; i++) {
            int v = 1;
            while (n%i == 0) {
                n /= i;
                v++;
            }
            ret *= v;
        }
    }
    return ret;
}

int main(void) {
    //p2 ab - p(a+b)10^n = 0
    //=> (ap-10^n)(bp-10^n) = 100^n 
    //1) factor 100^n to find all ap,bp
    //2) find all possible p by finding p|gcd(ap,bp)
    //3) add this to total
    //=>1,2,4,5,10,20,25,50,100
    //11,12,14,15,20,30,35,60,110
    int ans = 0;
    for (int n = 1; n<=9; n++) {
        long l = 1;
        for (int m = 0; m<n; m++) l*=10;
        for (int i = 0; i<=2*n; i++) {
            for (int j = 0; j<=2*n; j++) {
                long v = 1;
                for (int m = 0; m<i; m++) v *= 2;
                for (int m = 0; m<j; m++) v *= 5;
                if (v>l) continue;
                long ap = v + l;
                long bp = l*l/v + l;
                long g = gcd(ap,bp);
                ans += d(g);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}