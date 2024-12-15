//https://projecteuler.net/problem=101
//Optimum Polynomial

#include <stdio.h>

int main(void) {
    long sum = 0;
    long seq[12] = {0};
    for (int i = 1; i<12; i++) {
        seq[i] = ((long) i*i*i*i*i*i*i*i*i*i*i + 1) / (i+1);
    }
    for (int len = 0; len<11; len++) {
        long diffs[12][12] = {{0}};
        for (int i = 1; i<=len; i++) {
            diffs[0][i] = seq[i];
        }
        for (int i = 0; i<len; i++) {
            for (int j = 1; j<=len-i; j++) {
                diffs[i+1][j] = diffs[i][j+1] - diffs[i][j];
            }
        }
        diffs[len-1][2] = diffs[len-1][1];
        for (int i = len-2; i>=0; i--) {
            diffs[i][len-i+1] = diffs[i][len-i] + diffs[i+1][len-i];
        }
        sum += diffs[0][len+1];
    }
    printf("%ld\n", sum);
    return 0;
}