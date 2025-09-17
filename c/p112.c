//https://projecteuler.net/problem=112
//Bouncy Numbers

#include <stdio.h>

int increasing(int n) {
    int p = 100;
    while (n>0) {
        if (n%10>p) {
            return 0;
        }
        p = n%10;
        n /= 10;
    }
    return 1;
}

int decreasing(int n) {
    int p = -1;
    while (n>0) {
        if (n%10<p) {
            return 0;
        }
        p = n%10;
        n /= 10;
    }
    return 1;
}

int bouncy(int n) {
    return !(decreasing(n) || increasing(n));
}

int gcd(a,b) {
    if (b == 0) return a;
    return gcd(b,a%b);
}

int main(void) {
    int a = 1;
    int b = 1;
    while (1) {
        int g = gcd(a,b);
        if ((a/g == 99 && b/g == 100)) {
            break;
        }
        a += bouncy(b);
        b++;
    }
    printf("%d\n", b);
    return 0;
}