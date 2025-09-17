//https://projecteuler.net/problem=113
//Non-bouncy Numbers

#include <stdio.h>

long long C(n,r) {
    // binomial coefficient nCr (n choose r) n!/r!(n-r)!
    int done[16] = {0};
    long long v = 1;
    for (int i = n-r+1; i<=n; i++) {
        v *= (long long) i;

        for (int j = 1; j<=r; j++) {
            if (!done[j] && v % j == 0) {
                v /= (long long) j;
                done[j]=1;
            }
        }
    }
    return v;
}

int main(void) {
    //number of increasing numbers <10^100 is just the number of ways of choosing a1...a9 such that 
    //a1+a2+a3...a9 < 100. This can be calculated using stars and bars as 109C9 - 1
    //it works similarly for decreasing numbers but 0 is included as it can be at the end. the number
    //of decreasing numbers is thus 110C10 - 1. There is also an overlap of 1000 numbers, so we subtract it off.
    long long v = C(110,10) + C(109,9) - 1002;
    printf("%lli\n", v);
    return 0;
}