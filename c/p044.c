//https://projecteuler.net/problem=44
//Pentagon Numbers

#include <stdio.h>
#include <math.h>

int isPentagonal(int n) {
    int s = sqrt((double)n * 2 / 3) + 1;
    return (s*(3*s-1)/2 == n);
}

int main(void) {
    int a = 1;
    int b,x,y;
    int found = 0;

    while (1) {
        for (b = 1; b<a; b++) {
            x = a*(3*a-1) / 2;
            y = b*(3*b-1) / 2;
            if (isPentagonal(x-y) && isPentagonal(x+y)) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
        a++;
    }

    printf("%d\n",x-y);

    return 0;
}