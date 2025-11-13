//https://projecteuler.net/problem=190
//Maximising a Weighted Product

#include <stdio.h>
#include <math.h>

int main(void) {
    //Using the A.M. G.M. inequality, we see that P_m is maximized when x_1,x_2,...x_m are in an arithmetic
    //progression. Thus, the answer is just product of (2*k/(m+1))^k over 1<=k<=m.
    long ans = 0;
    for (int m = 2; m<=15; m++) {
        double P = 1;
        for (int k = 1; k<=m; k++) 
            P *= pow((double) 2 * k / (m+1), k);
        ans += (long) P;
    }
    printf("%ld\n", ans);
    return 0;
}