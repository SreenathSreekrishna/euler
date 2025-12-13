//https://projecteuler.net/problem=229
//Four Representations Using Squares

#include <stdio.h>
#define N 2000000000L

unsigned char numRepr[N+1] = {0};

int main(void) {
    for (long a = 1; a*a<=N; a++) {
        for (long b = a;; b++) {
            long v = a*a+b*b;
            if (v > N) break;
            numRepr[v] |= 1;
        }
    }
    for (long a = 1; a*a<=N; a++) {
        for (long b = 1;; b++) {
            long v = a*a+2*b*b;
            if (v > N) break;
            numRepr[v] |= 2;
        }
    }
    for (long a = 1; a*a<=N; a++) {
        for (long b = 1;; b++) {
            long v = a*a+3*b*b;
            if (v > N) break;
            numRepr[v] |= 4;
        }
    }
    for (long a = 1; a*a<=N; a++) {
        for (long b = 1;; b++) {
            long v = a*a+7*b*b;
            if (v > N) break;
            numRepr[v] |= 8;
        }
    }
    int ans = 0;
    for (int i = 0; i<=N; i++) {
        if (numRepr[i] != 15) continue;
        ans++;
    }
    printf("%d\n", ans);
    return 0;
}