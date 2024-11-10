//https://projecteuler.net/problem=21
//Amicable Numbers

#include <stdio.h>

int d(int n) {
    int s = 0;
    for (int i = 1; i<n; i++) {
        if (n%i == 0) {
            s += i;
        }
    }
    return s;
}

int main(void) {
    int s = 0;
    for (int i = 1; i<10000; i++) {
        int b = d(i);
        if (b != i) {
            if (d(b) == i) {
                s += i;
            }
        }
    }
    printf("%d\n", s);
    return 0;
}