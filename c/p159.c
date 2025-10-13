//https://projecteuler.net/problem=159
//Digital Root Sums of Factorisations

#include <stdio.h>
#include <math.h>

int max = 0;

int drs(int n) {
    int v = n%9;
    return v ? v : 9;
}

void findMdrs(int factors[], int numfactors, int rem, int chain[], int chainlen)  {
    if (rem == 1) {
        int s = 0;
        for (int i = 0; i<chainlen; i++) {
            s += drs(chain[i]);
        }
        if (s>max) max = s;
        return;
    }
    for (int i = 0; i<numfactors; i++) {
        if ((chainlen>0 && factors[i] < chain[chainlen-1]) || factors[i] > rem) continue;
        if (rem % factors[i] == 0) {
            chain[chainlen] = factors[i];
            findMdrs(factors,numfactors,rem/factors[i], chain, chainlen+1);
        }
    }
}

int mdrs(int n) {
    max = 0;
    int factors[256] = {0};
    int numfactors = 0;
    int s = sqrt(n);
    for (int f = 2; f<=s; f++) 
        if (n%f == 0) {
            factors[numfactors++] = f;
            if (f*f != n) factors[numfactors++] = n/f;
        }
    factors[numfactors++] = n;
    int chain[32];
    findMdrs(factors,numfactors,n,chain,0);
    return max;
}

int main(void) {
    int ans = 0;
    for (int i = 2; i<1000000; i++) ans += mdrs(i);
    printf("%d\n", ans);
    return 0;
}