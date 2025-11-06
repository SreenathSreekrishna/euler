//https://projecteuler.net/problem=181
//Grouping Two Different Coloured Objects

#include <stdio.h>
#include <stdlib.h>

long long p(int m, int n) {
    long long **partitions = (long long **)malloc((m + 1) * sizeof(long long *));
    for (int i = 0; i <= m; i++) {
        partitions[i] = (long long *)calloc((n + 1),sizeof(long long));
    }

    partitions[0][0] = 1ULL;

    for (int a = 0; a <= m; a++) {
        for (int b = 0; b <= n; b++) {
            if (a == 0 && b == 0) continue;
            for (int i = a; i <= m; i++)
            for (int j = b; j <= n; j++)
                partitions[i][j] += partitions[i-a][j - b];
        }
    }

    long long ans = partitions[m][n];

    for (int i = 0; i <= m; i++) free(partitions[i]);
    free(partitions);
    return ans;
}

int main(void) {
    //Let p(m,n) be the number of such groupings with m black objects and n white objects.
    //Notice that this is equivalent to the number of "bipartite" partitions of (m,n).
    //For example, for (3,1), the seven partitions are listed below.
    //(3,1)
    //(3,0) (0,1)
    //(2,1) (1,0)
    //(2,0) (1,1)
    //(2,0) (1,0) (0,1)
    //(1,1) (1,0) (1,0)
    //(1,0) (1,0) (1,0) (0,1)

    printf("%llu\n", p(40,60));
    return 0;
}