//https://projecteuler.net/problem=25
//1000-digit Fibonacci Number

#include <stdio.h>

int main(void) {
    int num1[1000] = {0};
    int num2[1000] = {0};
    num1[0] = 1;
    num2[0] = 1;
    int i = 2;
    while (num1[999] == 0) {
        int carry = 0;
        for (int j = 0; j<1000; j++) {
            int v = num1[j] + num2[j] + carry;
            int tmp = v % 10;
            num2[j] = num1[j];
            num1[j] = tmp;
            carry = v / 10;
        }
        i++;
    }
    printf("%d\n", i);
    return 0;
}