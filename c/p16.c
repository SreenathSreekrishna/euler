//https://projecteuler.net/problem=16
//Power Digit Sum

#include <stdio.h>
#define n 100

int main(void) {
    int bigNumber[n] = {0};
    bigNumber[0] = 1;
    for (int i = 0; i<n; i++) {
        int carry = 0;
        for (int j = 0; j<n; j++) {
            int num = 2*bigNumber[j] + carry;
            carry = 0;
            if (num > 9) {
                int tmp = num % 10;
                carry = (num - tmp) / 10;
                num = tmp;
            }
            bigNumber[j] = num;
        }
    }
    int sum = 0;
    for (int i = 0; i<n; i++) {
        sum += bigNumber[i];
    }
    printf("%d\n", sum);
    return 0;
}