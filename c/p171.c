//https://projecteuler.net/problem=171
//Square Sum of the Digital Squares

#include <stdio.h>

long ans = 0;
int freq[10] = {0};
long long fact19 = 1; //19!
long place = 111111111;

long long factorial(int n) {
    long v = 1;
    for (int i = 2; i<=n; i++) v *= i;
    return v;
}

long getSum(int nums[]) {
    //returns the sum of all permutations of nums[0] 0s, nums[1] 1s ... etc. mod 10^9
    //this is just digit*111111111*multinomial coefficient for arranging all numbers excluding 1 digit
    long v = 0;
    for (int d = 1; d<10; d++) {
        if (!nums[d]) continue;
        long long curr = fact19;
        curr /= factorial(nums[d]-1);
        for (int d2 = 0; d2<10; d2++) {
            if (d2 == d) continue;
            curr /= factorial(nums[d2]);
        }
        curr %= 1000000000;
        curr *= place;
        curr *= d;
        curr %= 1000000000;
        v += curr;
        v %= 1000000000;
    }
    return v;
}

void addWays(int m, int currDigit, int digitsLeft) {
    //generate integers 0<n<10^2 whose square digit sum equals m
    if (currDigit == 0) {
        if (m) return;
        if (digitsLeft < 0) return;
        freq[0] = digitsLeft;
        ans += getSum(freq);
        ans %= 1000000000;
        return;
    }
    int s = currDigit*currDigit;
    int limit = m/s;
    if (limit > digitsLeft) limit = digitsLeft;
    for (int i = limit; i>=0; i--) {
        freq[currDigit] = i;
        addWays(m - i*s, currDigit-1, digitsLeft-i);
        freq[currDigit] = 0;
    }
}

int main(void) {
    //a1 + 4a2 + 9a3 + ... 81a9 = k^2
    //Notice that for 0<n<10^20, k^2 < 1620, so k <= 40
    fact19 = factorial(19);
    for (int k = 1; k<40; k++) {
        addWays(k*k,9,20);
    }
    printf("%ld\n", ans);
    return 0;
}