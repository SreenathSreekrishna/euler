//https://projecteuler.net/problem=178
//Step Numbers

#include <stdio.h>
#define N 40

long ans = 0;

long memo[1024][10][N] = {{{0}}}; //memoize by memo[freqMask][lastdigit][numleft]

long solve(int arr[], int idx, int freq[], int numLeft) {
    int mask = 0;
    for (int i = 0; i<10; i++) {
        mask *= 2;
        mask += (freq[i] > 0);
    }
    int v = arr[idx-1];

    if (memo[mask][v][numLeft]) return memo[mask][v][numLeft];

    if (numLeft == 0) {
        for (int i = 0; i<10; i++) 
            if (!freq[i]) return 0;
        memo[mask][v][numLeft] = 1;
        return 1;
    }

    long ret = 0;
    if (v != 0) {
        arr[idx] = v-1;
        freq[v-1]++;
        ret += solve(arr, idx+1, freq, numLeft-1);
        freq[v-1]--;
    }
    if (v != 9) {
        arr[idx] = v+1;
        freq[v+1]++;
        ret += solve(arr, idx+1, freq, numLeft-1);
        freq[v+1]--;
    }
    memo[mask][v][numLeft] = ret;
    return ret;
}

int main(void) {
    for (int numLen = 10; numLen <= N; numLen++) {
        int a[N] = {0};
        int f[10] = {0};
        for (int start = 1; start<=9; start++) {
            a[0] = start;
            f[start]++;
            ans += solve(a, 1, f, numLen-1);
            f[start]--;
        }
    }
    printf("%ld\n", ans);
    return 0;
}