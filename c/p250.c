//https://projecteuler.net/problem=250
//250250

#include <stdio.h>
#define MOD 10000000000000000

int nnmod250(int n) {
    //n^n mod 250
    int e = n%100;
    if (!e) e += 100;
    n %= 250;
    int ret = 1;
    for (int i = 0; i<e; i++) {
        ret *= n;
        ret %= 250;
    }
    return ret;
}

int main(void) {
    int num[250251] = {0}; //n^n mod 250
    for (int i = 1; i<=250250; i++) num[i] = nnmod250(i);
    long numRepr[250] = {0}; //number of sets with sum i mod 250
    long prev[250] = {0};
    numRepr[0] = prev[0] = 1; //empty set has sum 0 mod 250
    for (int i = 1; i<=250250; i++) {
        for (int j = 0; j<250; j++) {
            int v = (num[i]+j) % 250;
            numRepr[v] += prev[j];
            numRepr[v] %= MOD;
        }
        for (int j = 0; j<250; j++) prev[j] = numRepr[j];
    }
    printf("%ld\n", numRepr[0]-1);
    return 0;
}