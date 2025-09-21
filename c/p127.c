//https://projecteuler.net/problem=127
//abc-hits

#include <stdio.h>

int rad(long n) {
    int r = 1;
    while (n>1) {
        for (long i = 2; i <= n; i++) {
            if (n % i != 0) continue;
            r *= i;
            while (n % i == 0) {
                n /= i;
            }
            break;
        }
    }
    return r;
}

int gcd(int a, int b) {
    while (b) {
        int tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

int main(void) {
    int r[120000] = {1000000};
    long s = 0;
    for (int i = 1; i<120000; i++) r[i] = rad(i);
    for (int c = 1; c<120000; c++) {
        for (int b = c/2; b<c; b++) {
            int a = c-b;
            if ((long) r[a]*r[b]*r[c] >= c) continue;
            if (gcd(a,b) != 1) continue;
            s+=c;
        }
    }
    printf("%li\n", s);
    return 0;
}