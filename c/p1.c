//https://projecteuler.net/problem=1
//Multiples of 3 or 5

#include <stdio.h>

int main(void) {
    int n = 1000;
    long sum = 0;
    for (int i = 0; i<n; i++) {
        if (i % 5 == 0 || i % 3 == 0) {
            sum += i;
        }
    }
    printf("%li\n", sum);
}