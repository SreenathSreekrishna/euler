//https://projecteuler.net/problem=88
//Product-sum Numbers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minProdSum[12001];

void findSol(int n, int targetSum, int targetProd) {
    minProdSum[targetProd - targetSum] = minProdSum[targetProd - targetSum] > targetProd ? targetProd : minProdSum[targetProd - targetSum];
    for (int i = n; i<=12002; i++) {
        int p = targetProd * i;
        int s = targetSum + i - 1;
        if (p - s > 12000) {
            break;
        }
        findSol(i,s,p);
    }
}

int main(void) {
    memset(minProdSum,0x42,sizeof(minProdSum));
    findSol(2,0,1);
    int solutions[24001] = {0};
    for (int i = 2; i<=12000; i++) {
        solutions[minProdSum[i]] = 1;
    }
    int sum = 0;
    for (int i = 0; i<24001; i++) {
        if (solutions[i]) {
            sum += i;
        }
    }
    printf("%d\n", sum);
    return 0;
}