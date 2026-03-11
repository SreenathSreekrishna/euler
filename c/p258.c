//https://projecteuler.net/problem=258
//A Lagged Fibonacci Sequence

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 2000
#define MOD 20092010
#define K (long) 1e18

void multpoly(long *a, long *b, long *out, long *tmp) {
    memset(tmp, 0, (2*N)*sizeof(long));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long prod = (long)(( (long long)a[i] * (long long)b[j] ) % MOD);
            tmp[i + j] += prod;
            if (tmp[i + j] >= (long)MOD) tmp[i + j] %= MOD;
        }
    }
    for (int i = 2 * N - 2; i >= N; i--) {
        long t = tmp[i] % MOD;
        if (!t) continue;
        tmp[i] = 0;
        tmp[i - N] += t;
        if (tmp[i - N] >= MOD) tmp[i - N] %= MOD;
        tmp[i - N + 1] += t;
        if (tmp[i - N + 1] >= MOD) tmp[i - N + 1] %= MOD;
    }
    for (int i = 0; i < N; i++) out[i] = tmp[i] % MOD;
}

int main(void) {

    long *init = calloc(N, sizeof(long));
    long *v = calloc(N, sizeof(long));
    long *nv = calloc(N, sizeof(long));
    for (int i = 0; i < N; i++) v[i] = 1;

    for (int i = 0; i < N; i++) {
        init[i] = v[0]%MOD;
        for (int j = 0; j < N-1; j++) nv[j] = v[j+1];
        nv[N-1] = (v[0]+v[1])%MOD;
        memcpy(v, nv, sizeof(long) * N);
    }

    long *poly = (long *)malloc(sizeof(long) * N);
    long *tmp = (long *)malloc(sizeof(long) * 4 * N);
    
    memset(poly, 0, sizeof(long) * N);
    poly[0] = 1;

    long *base = (long *)malloc(sizeof(long) * N);
    memset(base, 0, sizeof(long) * N);
    base[1] = 1;
    long val = K;

    while (val) {
        if (val % 2) {
            multpoly(poly, base, tmp, tmp+2*N);
            memcpy(poly, tmp, sizeof(long) * N);
        }
        multpoly(base, base, tmp, tmp+2*N);
        memcpy(base, tmp, sizeof(long) * N);
        val /= 2;
    }
    free(base);

    long ans = 0;
    for (int i = 0; i < N; i++) {
        if (!poly[i] || !init[i]) continue;
        ans = (ans + (poly[i]%MOD)*(init[i]%MOD)) % MOD;
    }

    printf("%ld\n", (ans % MOD));

    free(init);
    free(v);
    free(nv);
    free(poly);
    free(tmp);
    return 0;
}