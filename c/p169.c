//https://projecteuler.net/problem=169
//Sums of Powers of Two

#include <stdio.h>

int main(void) {
    //notice that we can redefine f(n) as just the number of representations of n in binary but instead
    //of the usual 0 and 1 digits being allowed, also allowing a 2 digit to account for the same power of
    //2 being used twice.
    //this can be counted using a dp kind of approach.
    // dp[i][j] stores number of representations of the least i significant digits along with current digit
    // j in this modified binary. thus, to add to the dp at each loop iteration i convert from modified
    //binary back into normal binary and check that the bit matches. if so, a valid sequence has been found.

    long long v = 1;
    for (int i = 0; i<25; i++) v *= 5;
    int bits[96] = {0};
    int idx = 25;
    while (v>0) {
        bits[idx++] = v%2;
        v /= 2;
    }
    long long dp[96][3] = {0};
    dp[0][0] = 1;
    for (int i = 0; i < idx; i++) {
        for (int j = 0; j <= 2; j++) {
            long long numWays = dp[i][j];
            for (int c = 0; c <= 2; c++) {
                int sum = c + j;
                if ((sum % 2) == bits[i]) {  
                    int cout = (sum - bits[i]) / 2;
                    if (cout <= 2) dp[i+1][cout] += numWays;
                }
            }
        }
    }
    printf("%lld\n", dp[idx][0]);
    return 0;
}