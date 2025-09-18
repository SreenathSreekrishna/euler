//https://projecteuler.net/problem=117
//Red, Green, and Blue Tiles

#include <stdio.h>

int main(void) {
    long numWays[51] = {1,1,2,4,8};
    for (int i = 5; i<=50; i++) {
        numWays[i] = numWays[i-1] + numWays[i-2] + numWays[i-3] + numWays[i-4];
    }
    printf("%li\n", numWays[50]);
    return 0;
}