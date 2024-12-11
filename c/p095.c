//https://projecteuler.net/problem=95
//Amicable Chains

#include <stdio.h>

int sumDiv[1000001];

int chainLen(int n) {
    int chain[1000000];
    int i = 0;
    int m = n;
    while (1) {
        chain[i] = m;
        m = sumDiv[m];
        if (m > 1000000) {
            return 0;
        }
        for (int j = 0; j<i; j++) {
            if (chain[j] == m) {
                if (j) return 0;
                return i-j;
            }
        }
        i++;
    }
}

int main(void) {
    for (int i = 0; i<=1000000; i++) {
        sumDiv[i] = 1;
    }
    for (int i = 2; i< 500000; i++) {
        for (int j = i * 2; j<=1000000; j+=i) {
            sumDiv[j] += i;
        }
    }
    int max = -1;
    int v = -1;
    for (int i = 2; i<=1000000; i++) {
        int l = chainLen(i);
        if (l > max) {
            max = l;
            v = i;
        }
    }
    printf("%d\n", v);

    return 0;
}