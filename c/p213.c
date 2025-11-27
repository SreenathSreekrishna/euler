//https://projecteuler.net/problem=213
//Flea Circus

#include <stdio.h>
#define N 30
#define M 50

int numNeighbours(int a, int b) {
    int num = !!a + !!b;
    if (a<N-1) num++; if (b<N-1) num++;
    return num;
}

int main(void) {
    double prob[N*N][N][N] = {0}; //probability that flea i is in location j,k.
    for (int i = 0; i<N; i++)
    for (int j = 0; j<N; j++)
        prob[N*i+j][i][j] = 1; //initially, assign each flea to its unique location
    
    for (int _ = 0; _<M; _++)
    for (int i = 0; i<N*N; i++) {
        double newProb[N][N] = {0};
        for (int j = 0; j<N; j++)
        for (int k = 0; k<N; k++) {
            double n = numNeighbours(j,k);
            double p = prob[i][j][k] / n; //the flea has an equal chance to go to any of its neighbours
            if (j) newProb[j-1][k] += p;
            if (k) newProb[j][k-1] += p;
            if (j<N-1) newProb[j+1][k] += p;
            if (k<N-1) newProb[j][k+1] += p;
        }
        for (int j = 0; j<N; j++)
        for (int k = 0; k<N; k++)
            prob[i][j][k] = newProb[j][k];
    }

    double ans = 0;
    for (int i = 0; i<N; i++)
    for (int j = 0; j<N; j++) {
        double p = 1;
        for (int flea = 0; flea<N*N; flea++) p *= (1-prob[flea][i][j]);
        ans += p;
    }
    printf("%.6f\n", ans);
    return 0;
}