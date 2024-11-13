//https://projecteuler.net/problem=62
//Cubic Permutations

#include <stdio.h>
#define N 100000

int sameFreq(int freq1[10], int freq2[10]) {
    for (int i = 0; i<10; i++) {
        if (freq1[i] != freq2[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    //permutations of the same number have the same frequency table for their digits

    long cubes[N];
    int freqs[N][10] = {{0}};
    int freqtable[N] = {0};

    for (int i = 0; i<N; i++) {
        long n = (long) i*i*i;
        int j = 0;
        while (n!=0) {
            freqs[i][n%10]++;
            n/=10;
            j++;
        }
    }

    for (int i = 0; i<N; i++) {
        for (int j = i; j<N; j++) {
            if (sameFreq(freqs[i],freqs[j])) {
                freqtable[i]++;
                if (freqtable[i] >= 5) {
                    printf("%li\n", (long) i*i*i);
                    return 0;
                }
            }
        }
    }
}