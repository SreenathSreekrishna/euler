//https://projecteuler.net/problem=201
//Subsets with a Unique Sum

#include <stdio.h>
#include <stdlib.h>
#define N 100
#define k 50

int main(void) {
    int MAX = 0;
    for (int i = 0; i<k; i++) MAX += (N-i)*(N-i);
    unsigned char **numWays = malloc(sizeof(unsigned char *) * (k+1));
    for (int i = 0; i<=k; i++) numWays[i] = calloc(MAX+1, sizeof(unsigned char));
    numWays[0][0] = 1;
    for (int i = 1; i<=N; i++) {
        int sq = i*i;
        for (int j = 49; j>=0; j--)
        for (int l = MAX-sq; l>=0; l--) {
            if (numWays[j][l] > 0) {
                if (numWays[j+1][l+sq] >= 2) continue;
                numWays[j+1][l+sq] += numWays[j][l];
            }
        }
    }
    long ans = 0;
    for (int i = 0; i<=MAX; i++)
        if (numWays[50][i] == 1) ans += i;
    printf("%ld\n", ans);
    for (int i = 0; i<=k; i++) free(numWays[i]);
    free(numWays);
    return 0;
}