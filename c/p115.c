//https://projecteuler.net/problem=115
//Counting Block Combinations II

#include <stdio.h>
#define m 50

int main(void) {
    int numWays[1024];
    for (int i = 0; i<m; i++) {
        numWays[i] = 1;
    }
    for (int i = m; i<=2*m; i++) {
        numWays[i] = (i-m+1)*(i-m+2)/2+1;
    }
    int n = 0;
    int i;
    for (i = 2*m+1; n<=1000000; i++) {
        n = i-1;
        for (int j = m; j<i; j++) {
            n += (j-m+1) * numWays[i-j-1];
        }
        numWays[i] = n;
    }
    printf("%d\n", i-1);
    return 0;
}