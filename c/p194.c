//https://projecteuler.net/problem=194
//Coloured Configurations

#include <stdio.h>
#define MOD 100000000
#define COLORS 1984
#define A 25
#define B 75

int numFixedA, numFixedB;
int memo[A+1][B+1] = {{0}};

int N(int a, int b) {
    if (memo[a][b]) return memo[a][b];
    int ret = 0;
    if (a) ret = ((long) numFixedA * N(a-1,b) + ret) % MOD;
    if (b) ret = ((long) numFixedB * N(a,b-1) + ret) % MOD;
    memo[a][b] = ret;
    return ret;
}

int main(void) {
    //Solved this using basic combinatorics.
    //precomputed the number of 1984 colorings of the units A and B online using chromatic polynomial.
    //these come out to 120393188855507580745344 for A and 120453932124036087937536 for B.
    //using these i compute number of colorings with left two colors fixed in numFixed for combi. this
    //is just A/(1984*1983) and B/(1984*1983)
    //then just run a basic dfs with combi to solve.

    memo[1][0] = 80745344;
    memo[0][1] = 87937536;
    numFixedA = 65269402;
    numFixedB = 84582888;
    printf("%d\n", N(A,B));
    return 0;
}