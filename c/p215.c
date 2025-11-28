//https://projecteuler.net/problem=215
//Crack-free Walls

#include <stdio.h>
#define M 32
#define N 10

unsigned char rows[100000][M/2 + 2] = {0};
int numRows = 0;
long memo[100000][N+1];

void getAllRows(unsigned char currentRow[], int idx, int numLeft) {
    if (numLeft == 0) {
        for (int i = 0; i < idx; i++) rows[numRows][i] = currentRow[i];
        numRows++;
        return;
    }
    if (numLeft == 1) return;
    currentRow[idx] = 2;
    getAllRows(currentRow, idx+1, numLeft-2);
    if (numLeft < 3) return;
    currentRow[idx] = 3;
    getAllRows(currentRow, idx+1, numLeft-3);
}

int checkCrack(int r1, int r2) {
    //check if row at idx r1 and r2 have shared crack
    int s1[M/2 + 2] = {rows[r1][0]};
    int s2[M/2 + 2] = {rows[r2][0]};
    int len1, len2;
    for (len1 = 1; rows[r1][len1]; len1++) s1[len1] = s1[len1-1] + rows[r1][len1];
    for (len2 = 1; rows[r2][len2]; len2++) s2[len2] = s2[len2-1] + rows[r2][len2];
    int i = 0; int j = 0;
    while (i < len1 && j < len2) {
        if (s1[i] != M && s1[i] == s2[j]) return 1;
        else if (s1[i] < s2[j]) i++;
        else j++;
    }
    return 0;
}

long getNumPossibilities(int prevrow, int rowsLeft) {
    if (memo[prevrow][rowsLeft] != -1) return memo[prevrow][rowsLeft];
    if (rowsLeft == 0) return 1;
    long ret = 0;
    for (int i = 0; i < numRows; i++) {
        if (checkCrack(i, prevrow)) continue;
        ret += getNumPossibilities(i, rowsLeft-1);
    }
    memo[prevrow][rowsLeft] = ret;
    return ret;
}

int main(void) {
    for (int i = 0; i < 100000; i++)
        for (int j = 0; j <= N; j++) memo[i][j] = -1;

    unsigned char currow[M/2 + 2] = {0};
    getAllRows(currow, 0, M);

    long ans = 0;
    // choose each possible bottom row, then place N-1 more above it
    for (int i = 0; i < numRows; i++) ans += getNumPossibilities(i, N-1);
    printf("%ld\n", ans);
    return 0;
}
