//https://projecteuler.net/problem=116
//Red, Green or Blue Tiles

#include <stdio.h>

int main(void) {
    long tiles2[51] = {0,0,1,2,4,7,12,20};
    long tiles3[51] = {0,0,0,1,2,3,5,8};
    long tiles4[51] = {0,0,0,0,1,2,3,4};
    for (int i = 8; i<=50; i++) {
        tiles2[i] = tiles2[i-1] + tiles2[i-2] + 1;
        tiles3[i] = tiles3[i-1] + tiles3[i-2] - tiles3[i-5];
        tiles4[i] = tiles4[i-1] + tiles4[i-3] - tiles4[i-7];
    }
    printf("%li\n",tiles2[50]+tiles3[50]+tiles4[50]);
    return 0;
}