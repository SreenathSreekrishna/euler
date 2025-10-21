//https://projecteuler.net/problem=164
//Three Consecutive Digital Sum Limit

#include <stdio.h>
#define N 20

int main(void) {
    //let a[i][j] be the number of integers with i digits ending with 2 digits j satisfying the property.
    //Notice that we can now fill out the recurrence using just a[1][j] and a[2][j]
    long a[N+1][100] = {{0}};
    long ans = 0;
    for (int i = 0; i<100; i++) {
        if (i/10 + i%10 <= 9) a[2][i] = 1;
    }
    for (int i = 3; i<=N; i++) {
        for (int d = 0; d<100; d++) {
            int m = 9-(d/10+d%10);
            for (int v = 0; v<=m; v++) {
                a[i][10*(d%10)+v] += a[i-1][d];
            }
        }
    }
    for (int i = 0; i<100; i++) {
        ans += a[N][i];
        ans -= a[N-1][i];
    }
    printf("%ld\n",ans);
    return 0;
}