//https://projecteuler.net/problem=158
//Lexicographical Neighbours

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
    //132 213 231 312
    //Let L(n) be the number of permutations of 1...n such that there exists exactly one i such that
    //a_i > a_(i-1). Notice that p(n) is just 26Cn * L(n).
    //Notice that for all permutations with this property, we can split 'a' into two parts which are
    //both decreasing, with the first element of the second part being greater than the last element
    //of the first part. The number of ways to do this comes out to the sum of nCk - 1 over 1<=k<n.
    //This comes out to L(n) = 2^n - n - 1
    long power = 4;
    long long max = 0;
    for (int i = 2; i<=26; i++) {
        int v = i;
        if (i > 13) v = 26-i;
        long long p = C(26,v)*(power - i - 1);
        if (p>max) max = p;
        power *= 2;
    }
    printf("%lld\n", max);
    return 0;
}