//https://projecteuler.net/problem=106
//Special Subset Sums: Meta-testing

#include <stdio.h>

int C(n,r) {
    // binomial coefficient nCr (n choose r) n!/r!(n-r)!
    int v = 1;
    for (int i = n-r+1; i<=n; i++) {
        v *= i;
    }
    for (int i = 1; i<=r; i++) {
        v /= i;
    }
    return v;
}

int main(void) {
    /* By considering the sets as {a1,a2,a3,...a_n} in increasing order; we can find out how many
     "necessary" comparisons are needed. Notice that we only need to consider disjoint subject of equal 
     cardinality due to rule 2 being satisfied. We split up the problem into finding the number of 
     necessary comparisons of subsets of cardinality 2,3, ... floor(n/2). First we find the number of 
     unnecessary comparisons for example, a1 + a2 and a3 + a4, as the latter is always greater than the 
     former. This can be done by finding the number of ways to choose two subsets such that each element
     of one of the subsets is always greater than the corresponding element in the first one. For example, 
     {a1,a3,a7} and {a2,a8,a9}. The number of ways to choose two subsets of cardinality k from a set of
     cardinality 2k turns out to be the nth catalan number. The number of remaining ways to choose subsets
     is thus R(k) = (k-1)(2k)!/(2(k+1)(k!)^2) = (2k-1)C(k-2) after simplification. As these 2k elements can be chosen from
     the n elements of our original set in (n)C(2k) ways, we simply multiply this binomial coefficient with
     each corresponding k and then sum to find the total number of necessary comparisons. This comes out to
     nC4*R(2) + nC6*R(3) + nC8*R(4) ... nC(2floor(n/2))*R(floor(n/2)) */

    int n = 12;
    int sol = 0;
    for (int i = 4; i<=n; i+=2) {
        sol += C(n,i) * C(i-1, i/2 - 2);
    }
    printf("%d\n", sol);
    return 0;
}