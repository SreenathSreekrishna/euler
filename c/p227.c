//https://projecteuler.net/problem=227
//The Chase

#include <stdio.h>
#define N 100

int dist(int x) {
    x = (x+2*N) % N;
    if (x > N/2) return N-x;
    return x;
}

int main(void) {
    //suppose the first ball is in position 0 and second ball is in position x. Let E(x) be the expected
    //number of turns from this position for the game to stop. Notice that because of this, we can enumerate
    //all possibilities and find a recurrence for E(x). (We only need one variable as only the distance bet-
    //ween the balls matters due to rotational symmetry).
    //E(x) = (2E(x)+E(x-2)+E(x+2))/36 + 2(E(x-1)+E(x+1))/9 + 4E(x)/9 + 1
    //=> E(x) = 4(E(x-1)+E(x+1))/9 + (E(x-2)+E(x+2))/18 + 2
    //=> E(x+2) = 18E(x) - 8(E(x-1)+E(x+1)) - E(x-2) - 36
    //i just solve the system of linear equations using gaussian elimination (solve Ax=b) for coefficient 
    //matrix A and solution vector b.
    double A[N/2+1][N/2+1], b[N/2+1], E[N/2+1];
    for(int i = 0; i<=N/2; i++) {
        for (int j = 0; j<=N/2; j++) A[i][j] = 0;
        b[i]=0; E[i]=0;
    }
    A[0][0] = 1; b[0] = 0;

    //fill coefficient matrix
    for(int i = 1; i<=N/2; i++) {
        A[i][i] = 1.0;
        A[i][dist(i-1)] -= 4.0/9.0;
        A[i][dist(i+1)] -= 4.0/9.0;
        A[i][dist(i-2)] -= 1.0/18.0;
        A[i][dist(i+2)] -= 1.0/18.0;
        b[i] = 2.0;
    }
    for(int k = 0; k<=N/2; k++)
    for(int i = k+1; i<=N/2; i++) {
        double f = A[i][k] / A[k][k];
        for(int j = k; j<=N/2; j++) A[i][j] -= f*A[k][j];
        b[i] -= f*b[k];
    }
    //compute all E
    for(int i = N/2; i>=0; i--) {
        double s = b[i];
        for(int j = i+1; j<=N/2; j++) s -= A[i][j]*E[j];
        E[i] = s / A[i][i];
    }

    printf("%.6f\n", E[N/2]);
    return 0;
}