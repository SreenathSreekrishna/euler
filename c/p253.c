//https://projecteuler.net/problem=253
//Tidying Up A

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 40

double memo[N+1][N+1][N+1][2][2][N+1];
unsigned char seen[N+1][N+1][N+1][2][2];

double *dfs(int numPlaced, int maxBlocks, int numBlocks, int l, int r) {
    //returns pointer to array containing counts for final maxima m
    if (seen[numPlaced][maxBlocks][numBlocks][l][r]) 
        return memo[numPlaced][maxBlocks][numBlocks][l][r];

    seen[numPlaced][maxBlocks][numBlocks][l][r] = 1;

    double *res = memo[numPlaced][maxBlocks][numBlocks][l][r];
    memset(res, 0.0, N+1);

    if (numPlaced == N) {
        if (numBlocks == 1 && l == 1 && r == 1 && maxBlocks <= N) res[maxBlocks] = 1.0;
        return res;
    }

    if (!l) {
        double *t[2];
        if (numBlocks > 0) {
            t[0] = dfs(numPlaced + 1, maxBlocks, numBlocks, 1, r);
            t[1] = dfs(numPlaced + 1, maxBlocks, numBlocks, 0, r);
            for (int i = 0; i<2; i++)
            for (int j = 0; j<=N; j++) res[j] += t[i][j];
        }
        int newmax = (maxBlocks > (numBlocks + 1) ? maxBlocks : (numBlocks + 1));
        t[0] = dfs(numPlaced + 1, newmax, numBlocks + 1, 1, r);
        t[1] = dfs(numPlaced + 1, newmax, numBlocks + 1, 0, r);
        for (int i = 0; i<2; i++)
        for (int j = 0; j<=N; j++) res[j] += t[i][j];
    }

    if (!r) {
        double *t[2];
        if (numBlocks > 0) {
            t[0] = dfs(numPlaced + 1, maxBlocks, numBlocks, l, 1);
            t[1] = dfs(numPlaced + 1, maxBlocks, numBlocks, l, 0);
            for (int i = 0; i<2; i++)
            for (int j = 0; j<=N; j++) res[j] += t[i][j];
        }
        int newmax = (maxBlocks > (numBlocks + 1) ? maxBlocks : (numBlocks + 1));
        t[0] = dfs(numPlaced + 1, newmax, numBlocks + 1, l, 1);
        t[1] = dfs(numPlaced + 1, newmax, numBlocks + 1, l, 0);
        for (int i = 0; i<2; i++)
        for (int j = 0; j<=N; j++) res[j] += t[i][j];
    }

    for (int i = 0; i<2; i++) {
        double *t = dfs(numPlaced + 1, maxBlocks, numBlocks - 1 + i, l, r);
        for (int j = 0; j<=N; j++) res[j] += (double) (numBlocks-1) * (i+1) * t[j];
    }

    int newmax = (maxBlocks > (numBlocks + 1) ? maxBlocks : (numBlocks + 1));
    double *t = dfs(numPlaced + 1, newmax, numBlocks + 1, l, r);
    for (int j = 0; j<=N; j++) res[j] += (double) (numBlocks-1) * t[j];

    return res;
}

int main(void) {
    double ans[N + 1] = {0};

    double *r[3];

    r[0] = dfs(1, 1, 1, 0, 1);
    r[1] = dfs(1, 1, 1, 0, 0);
    r[2] = dfs(1, 1, 1, 1, 0);

    for (int i = 0; i<3; i++)
    for (int j = 0; j<=N; j++) ans[j] += r[i][j];

    double m = 0.0, n = 0.0;
    for (int i = 1; i <= N; i++) {
        double v = ans[i];
        m += (double) i * v;
        n += v;
    }
    
    printf("%.6f\n", m/n);
    return 0;
}