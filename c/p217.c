//https://projecteuler.net/problem=217
//Balanced Numbers

#include <stdio.h>
#define N 47
#define MOD 14348907 //3^15

int main(void) {
    //Let S(n) be sum of balanced numbers with exactly n digits.
    //notice that T(n) = sum from k=1 to n of S(k)
    //first we precompute the number and sums of integers of all lengths with given digit sums.
    long sums[9*(N/2)+1][N/2+1] = {0}; //sum of all the integers with exactly j digits whose digit sum is i
    long sums1[9*(N/2)+1][N/2+1] = {0}; //same as sums but no leading zeroes allowed in the integers
    long numNums[9*(N/2)+1][N/2+1] = {0}; //number of integers with exactly j digits whose digit sum is i.
    for (int i = 0; i<=N/2; i++) numNums[0][i] = 1; //exactly one number (all zeroes) with digit sum 0
    long pow10[N+1] = {1};
    for (int i = 1; i<=N; i++) {
        pow10[i] = (10L*pow10[i-1]) % MOD;
    }
    for (int i = 1; i<=9*(N/2); i++) {
        for (int j = 1; j<=N/2; j++) {
            //we have to calculate the number and sum of integers with j digits and digit sum i.
            for (int first = 0; first<10; first++) {
                int remaining = i - first;
                if (remaining < 0) continue;
                numNums[i][j] = (numNums[i][j] + numNums[remaining][j-1]) % MOD;
                long num = (pow10[j-1] * first) % MOD;
                long val = (num * numNums[remaining][j-1] + sums[remaining][j-1]) % MOD;
                sums[i][j] = (sums[i][j] + val) % MOD;
                if (first) sums1[i][j] = (sums1[i][j] + val) % MOD;
            }
        }
    }
    //now we can just calculate S(k) by combining using powers of 10 and basic combi multiplicity principle.
    long S[N+1] = {0};
    for (int i = 1; i<=N; i++) {
        if (i%2 == 0) {
            for (int j = 1; j<=9*(i/2); j++) {
                long numLeft = numNums[j][i/2] - numNums[j][i/2 - 1];
                long numRight = numNums[j][i/2];
                long sumLeft = sums1[j][i/2];
                long sumRight = sums[j][i/2];
                long l = (sumLeft*(numRight*pow10[i/2]%MOD)%MOD); 
                long r = (sumRight*numLeft)%MOD;
                S[i] += (l+r)%MOD;
                S[i] %= MOD;
            }
        } else {
            if (i == 1) S[i] = 45;
            for (int j = 1; j<=9*(i/2); j++) {
                long numLeft = numNums[j][i/2] - numNums[j][i/2 - 1];
                long numRight = numNums[j][i/2];
                long sumLeft = sums1[j][i/2];
                long sumRight = sums[j][i/2];
                long l = (sumLeft*(numRight*pow10[i/2 + 2]%MOD))%MOD;
                long m = (45L*((numLeft*(numRight*pow10[i/2]%MOD))%MOD))%MOD;
                long r = (10*sumRight*numLeft)%MOD;
                S[i] += (l+m+r) % MOD;
                S[i] %= MOD;
            }
        }
    }
    
    long ans = 0;
    for (int i = 1; i<=N; i++) ans += S[i]%MOD;
    printf("%ld\n", ans%MOD);
    return 0;
}