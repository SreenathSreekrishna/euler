//https://projecteuler.net/problem=6
//Sum square difference

#include <stdio.h>

int main(void) {
    //simple math solution
    int n = 100;
    int res = (n*n*(n+1)*(n+1)/4) - (n*(n+1)*(2*n+1)/6);
    printf("%d\n", res);
    return 0;
}