//https://projecteuler.net/problem=92
//Square Digit Chains

#include <stdio.h>

int digitSquare(int n) {
    int s = 0;
    while (n > 0) {
        s+= (n%10)*(n%10);
        n /= 10;
    }
    return s;
}

int main(void) {
    int t = 0;
    for (int i = 2; i<10000000; i++) {
        int v = i;
        while (1) {
            v = digitSquare(v);
            if (v == 89 || v == 1) {
                break;
            }
        }
        t += (v == 89);
    }
    printf("%d\n", t);

    return 0;
}