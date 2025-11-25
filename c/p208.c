//https://projecteuler.net/problem=208
//Robot Walks

#include <stdio.h>
#define N 70

long memo[(N/5+1)*(N/5+1)*(N/5+1)*(N/5+1)*(N/5+1)][5];

long numPossibilities(int freq[5], int lastChosen) {
    long encoded = 0;
    int idx = 0;
    for (int i = 0; i<5; i++) {
        encoded *= (N/5+1);
        encoded += freq[i];
        idx += freq[i];
    }
    if (memo[encoded][lastChosen] != -1) return memo[encoded][lastChosen];

    if (idx == N) {
        memo[encoded][lastChosen] = 1;
        return 1;
    }
    if (!idx) {
        freq[0] = 1;
        return numPossibilities(freq, 0);
    }
    long ret = 0;
    if (freq[lastChosen] < N/5) {
        freq[lastChosen]++;
        ret += numPossibilities(freq, lastChosen);
        freq[lastChosen]--;
    }
    int nextChosen = (lastChosen+1)%5;
    if (freq[nextChosen] < N/5) {
        freq[nextChosen]++;
        ret += numPossibilities(freq, nextChosen);
        freq[nextChosen]--;
    }
    memo[encoded][lastChosen] = ret;
    return ret;
}

int main(void) {
    int len = sizeof(memo) / (5*sizeof(long));
    for (int i = 0; i<len; i++) {
        for (int k = 0; k<5; k++) memo[i][k] = -1;
    }
    int freq[5] = {0};
    printf("%ld\n", 2*numPossibilities(freq, 0)); //multiply by 2 to consider flipped version of same path
    return 0;
}