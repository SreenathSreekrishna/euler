//https://projecteuler.net/problem=145
//Reversible Numbers

#include <stdio.h>

int reverse(int n) {
    int r = 0;
    while (n>0) {
        r*=10;
        r += (n%10);
        n /= 10;
    }
    return r;
}

int oddest(int n) {
    while (n>0) {
        if (n%2 == 0) return 0;
        n /= 10;
    }
    return 1;
}

int main(void) {
    int num = 0;
    //there are no 9-digit solutions so i only check upto 10^8
    for (int i = 1; i<100000000; i++) {
        if (i%10 == 0) continue;
        if (!oddest(i+reverse(i))) continue;
        num++;
    }
    printf("%d\n", num);
    return 0;
}