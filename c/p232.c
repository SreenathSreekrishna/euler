//https://projecteuler.net/problem=232
//The Race

#include <stdio.h>
#define N 100

double pow2[32] = {1};

double memo[2*N+1][2*N+1] = {0};

double p2prob(int a, int b) {
    //returns prob that p2 will win given it is p2's turn with b points and p1 has a points
    if (memo[a][b] != -1) return memo[a][b];
    if (a >= N) {
        memo[a][b] = 0;
        return 0;
    }
    if (b >= N) {
        memo[a][b] = 1;
        return 1;
    }
    //p2 wants to choose n such that the total probability of winning is maximum.
    double prob = 0;
    for (int T = 1; T < 32; T++) {
        //if p2 chooses T, the probability will be p1prob(a,b+2^(T-1))/2^T + p1prob(a,b)(1-1/2^T)
        int newb = b+pow2[T-1];
        double p1prob2 = newb >= N ? 2 : p2prob(a,newb) + p2prob(a+1,newb);
        double v = (p1prob2 + (pow2[T]-1)*p2prob(a+1,b))/(pow2[T]+1);
        if (v > prob) prob = v;
    }
    memo[a][b] = prob;
    return prob;
}

int main(void) {
    for (int i = 0; i<=2*N; i++) for (int j = 0; j<=2*N; j++) memo[i][j] = -1;
    for (int i = 1; i<32; i++) pow2[i] = pow2[i-1]*2;
    printf("%.8f\n", 0.5*(p2prob(1,0)+p2prob(0,0)));
    return 0;
}