//https://projecteuler.net/problem=76
//Counting Summations

#include <stdio.h>

int main(void) {
    //we will use euler's pentagonal formula for partitions
    int partitions[101] = {0};
    partitions[0] = 1;
    partitions[1] = 1;
    int pent[16] = {1,2,5,7,12,15,22,26,35,40,51,57,70,77,92,100};
    for (int i = 2; i<=100; i++) {
        for (int j = 0; j<16; j++) {
            int n = i - pent[j];
            if (n < 0) {
                continue;
            }
            partitions[i] += (1-((j/2)%2)*2)*partitions[n];
        }
    }
    printf("%d\n",partitions[100]-1);
    return 0;
}