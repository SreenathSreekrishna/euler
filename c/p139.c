//https://projecteuler.net/problem=139
//Pythagorean Tiles

#include <stdio.h>

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b,a%b);
}

int main(void) {
    //a+b+c < 100000000
    //2n^2 + 2mn < 100000000
    //2n(m+n) < 100000000
    int num = 0;
    for (int m = 1; m<7071; m++) {
        for (int n = m+1; 2*n*(m+n)<100000000; n++) {
            if (gcd(m,n)!=1) continue;
            int a = 2*m*n;
            int b = n*n-m*m;
            int c = n*n+m*m;
            if (gcd(a,b)!=1) continue;
            if (c % (a-b)) continue;
            num += 100000000 / (2*n*(m+n));
            if (100000000 % (2*n*(m+n)) == 0) num--;
        }
    }
    printf("%d\n", num);
    return 0;
}