//https://projecteuler.net/problem=28
//Number Spiral Diagonals

#include <stdio.h>

int main(void) {
    int n = 1001;
    int k = 1;
    int res = 0;
    for (int i = 2; i<n; i+=2) {
        for (int j = 0; j<4; j++) {
            res += k;
            k += i;
        }
    }
    res += k;
    printf("%d\n", res);
}