//https://projecteuler.net/problem=110
//Diophantine Reciprocals II

#include <stdio.h>

long long power(int p, int n) {
    long long v = 1;
    if (n >=32) return -1;
    for (int i = 0; i<n; i++) v *= (long long) p;
    return v;
}

int main(void) {
    int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
    long long min = __LONG_LONG_MAX__;
    int composite[8192];
    int compLen = 0;
    for (int i  = 1; i<=10001; i+=2) {
        int n = i;
        int j = 2;
        int count = 0;
        while (n>1) {
            while (n % j == 0) {
                n /= j;
                count++;
            }
            j++;
        }
        if (count <= 4) continue;
        composite[compLen] = i;
        compLen++;
    }
    for (int i = 0; i<compLen; i++) {
    for (int l = 0; l<=i; l++) {
        int n = composite[i]*composite[l];
        if (n < 8000000) continue;
        int j = 2;
        int count = 0;
        int factors[32] = {0};
        while (n>1) {
            while (n % j == 0) {
                n /= j;
                factors[count] = j;
                count++;
            }
            j++;
        }
        if (count <= 9) continue;

        long long val = 1;
        for (int k = 0; k<count; k++) {
            long long v = power(primes[k], factors[count - k - 1] / 2);
            if (v>0) {
                val *= v;
            }
            else {
                break;
            }
        }
        if (val < min && val>1) min = val;
    }}
    printf("%lli\n", min);
    return 0;
}