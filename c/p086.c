//https://projecteuler.net/problem=86
//Cuboid Route

#include <stdio.h>
#include <math.h>

int isSquare(int n) {
    int s = sqrt(n);
    return s*s == n;
}

int main(void) {
    int i = 1;
    int sols = 0;
    while (1) {
        for (int j = 1; j<=i; j++) {
            for (int k = 1; k<=j; k++) {
                //i>=j>=k
                //min path = sqrt(i^2 + (j+k)^2)

                int v = i*i + (j+k)*(j+k);
                if (isSquare(v)) {
                    sols++;
                }
            }
        }
        if (sols >= 1000000) {
            break;
        }
        i++;
    }
    printf("%d\n", i);
    return 0;
}