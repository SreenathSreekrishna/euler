//https://projecteuler.net/problem=20
//Factorial Digit Sum

#include <stdio.h>

int main(void) {
    int bigInt[256] = {0};
    bigInt[0] = 1;
    for (int i  = 2; i<=100; i++) {
        int carry = 0;
        for (int j = 0; j<256; j++) {
            int v = bigInt[j]*i + carry;
            bigInt[j] = v % 10;
            carry = v / 10;
        }
    }
    int s = 0;
    for (int i = 0; i<256; i++) {
        s += bigInt[i];
    }
    printf("%d\n", s);
    return 0;
}