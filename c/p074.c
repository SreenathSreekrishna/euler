//https://projecteuler.net/problem=74
//Digit Factorial Chains

#include <stdio.h>

int factorials[10] = {1,1,2,6,24,120,720,5040,40320,362880};

int digitFactorial(int k) {
    int n = 0;
    while (k != 0) {
        n += factorials[k%10];
        k /= 10;
    }
    return n;
}

int main(void) {
    int chain[100] = {0};
    int num = 0;
    for (int i = 0; i<1000000; i++) {
        int n = i;
        for (int j = 0; j<60; j++) {
            chain[j] = n;
            n = digitFactorial(n);
        }
        int repeat = 0;
        for (int j = 0; j<60; j++) {
            for (int k = 0; k<j; k++) {
                if (chain[j] == chain[k]) {
                    repeat = 1;
                    break;
                }
            }
            if (repeat) {
                break;
            }
        }
        if (!repeat) {
            num++;
        }
    }
    printf("%d\n", num);
    return 0;
}