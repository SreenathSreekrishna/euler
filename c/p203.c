//https://projecteuler.net/problem=203
//Squarefree Binomial Coefficients

#include <stdio.h>
#include <stdlib.h>
#define N 51

long long C(n,r) {
    // binomial coefficient nCr (n choose r) n!/r!(n-r)!
    int done[50] = {0};
    long long v = 1;
    for (int i = n-r+1; i<=n; i++) {
        v *= (long long) i;

        for (int j = 1; j<=r; j++) {
            if (!done[j] && v % j == 0) {
                v /= (long long) j;
                done[j]=1;
            }
        }
    }
    return v;
}

int vp(int n, int p) {
    //returns maximum power of p dividing n!
    int ret = 0;
    while (n > 0) {
        n /= p;
        ret += n;
    }
    return ret;
}

int sqfree(int n, int k) {
    //checks if binomial n choose k is squarefree
    unsigned char *IS_PRIME = malloc(sizeof(unsigned char) * N);
    int *primes = malloc(sizeof(int) * 1024);
    int numPrimes = 0;
    for (int p = 2; p<N; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<N; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    free(IS_PRIME);
    for (int i = 0; i<numPrimes; i++) {
        int pow = vp(n, primes[i]) - (vp(k, primes[i]) + vp(n-k, primes[i]));
        if (pow >= 2) {
            free(primes);
            return 0;
        }
    }
    free(primes);
    return 1;
}

int cmp(const void *a, const void *b) {
    if (*(long long*)a > *(long long*)b) return 1;
    if (*(long long*)a < *(long long*)b) return -1;
    return 0;
}

int main(void) {
    long long pascalnums[N*(N-1)/2 + 1] = {0};
    int numPascal = 0;
    for (int n = 0; n<N; n++) {
        for (int k = 0; k<=n/2; k++) {
            long long b = C(n,k);
            if (sqfree(n, k)) pascalnums[numPascal++] = b;
        }
    }
    qsort(pascalnums, numPascal, sizeof(long long), cmp);
    long long ans = 1;
    for (int i = 1; i<numPascal; i++)
        if (pascalnums[i] != pascalnums[i-1]) ans+=pascalnums[i];
    printf("%lld\n", ans);
    return 0;
}