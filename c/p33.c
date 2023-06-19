//https://projecteuler.net/problem=33
//Digit Cancelling Fractions

#include <stdio.h>

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main(void) {
    int num = 1;
    int den = 1;
    for (int i = 1; i<100; i++) {
        for (int j = 1; j<i; j++) {
            int oo = i % 10;
            int ot = i / 10;
            int to = j % 10;
            int tt = j / 10;
            if ((oo == tt && (float) ot / (float) to == (float) i / (float) j)
              ^ (ot == to && (float) oo / (float) tt == (float) i / (float) j)) {
                num *= j;
                den *= i;
            }
        }
    }
    printf("%d\n", den / gcd(num, den));
}