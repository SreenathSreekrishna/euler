//https://projecteuler.net/problem=237
//Tours on a 4xN Playing Board

#include <stdio.h>
#define N 1000000000000
#define MOD 100000000

void matmul(long a[4][4], long b[4][4], long c[4][4]) {
    long res[4][4] = {{0}};
    for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
            for (int k = 0; k<4; k++)
                res[i][j] += a[i][k]*b[k][j];
                res[i][j] %= MOD;
        }
    }
    for (int i = 0; i<4; i++)
        for (int j = 0; j<4; j++)
            c[i][j] = res[i][j];
}

int main(void) {
    //T(n) can be calculated using the recurrence T(n) = 2*T(n-1) + 2*T(n-2) - 2*T(n-3) + T(n-4)
    //we can represent this recurrence using the recurrence V(n+1) = AV(n) for matrix A given below (where V
    //represents four consecutive values of T).
    //A = 0   1   0   0
    //    0   0   1   0
    //    0   0   0   1
    //    1  -2   2   2
    //To compute V(n) for large n as given in the problem, i just have to find V(0)*A^n
    //A^n can be found using russian peasant multiplication (binary)
    long A[4][4] = {{0,1,0,0}, {0,0,1,0}, {0,0,0,1}, {1,-2,2,2}};
    long res[4][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
    long n = N;
    while (n > 0) {
        if (n % 2 == 1) matmul(res, A, res);
        matmul(A,A,A);
        n /= 2;
    }
    long ans[4][4] = {{0},{1},{1},{4}};
    matmul(res,ans,ans);
    printf("%ld\n", ans[0][0]);
    return 0;
}