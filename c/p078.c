//https://projecteuler.net/problem=78
//Coin Partitions

#include <stdio.h>
#define N 1000000

int partitions[10000009] = {0};

int main(void) {
    //we will use euler's pentagonal formula for partitions
    partitions[0] = 1;
    partitions[1] = 1;
    int pent[1632];
    for (int i = 0; i<816; i++) {
        pent[2*i] = (i+1)*(3*i+2) / 2;
        pent[2*i+1] = (i+1)*(3*i+4) / 2;
    }
    for (int i = 2; i<=1000009; i++) {
        for (int j = 0; j<1632; j++) {
            int n = i - pent[j];
            if (n < 0) {
                continue;
            }
            partitions[i] = (partitions[i] + (1-((j/2)%2)*2)*partitions[n]) % N;
        }
        if (partitions[i] == 0) {
            printf("%d\n", i);
            return 0;
        }
    }
}