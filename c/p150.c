//https://projecteuler.net/problem=150
//Sub-triangle Sums

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int triangle[1000][1000] ={{0}};
    long **sums = malloc(sizeof(long *)*1001);
    for (int i = 0; i<=1000; i++) {
        sums[i] = malloc(sizeof(long) * 1001);
        for (int j = 0; j<=1000; j++) sums[i][j]=0;
    }
    int t = 0;
    for (int i = 0; i<1000; i++) {
        for (int j = 0; j<=i; j++) {
            t = (615949LL*t+797807) % 0x100000L;
            triangle[i][j] = t-0x100000L/2;
            sums[i][j+1] = sums[i][j] + triangle[i][j];
        }
    }

    long min = 0;
    for (int i = 0; i<1000; i++) {
        for (int j = 0; j<=i; j++) {
            long sum = 0;
            for (int k = 1; k+i<1000; k++) {
                int r = i+k-1;
                sum += sums[r][j+k] - sums[r][j];
                if (sum<min) min = sum;
            }
        }
    }

    printf("%ld\n", min);
    for (int i = 0; i<=1000; i++) free(sums[i]);
    free(sums);
    return 0;
}