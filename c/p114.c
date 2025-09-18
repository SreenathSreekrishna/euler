//https://projecteuler.net/problem=114
//Counting Block Combinations I

#include <stdio.h>

int main(void) {
    long numWays[51] = {1,1,1,2,4,7,11};
    for (int i = 7; i<=50; i++) {
        long n = i-1;
        for (int j = 3; j<i; j++) {
            n += (long) (j-2) * numWays[i-j-1];
        }
        numWays[i] = n;
    }
    printf("%li\n", numWays[50]);
    return 0;
}