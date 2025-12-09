//https://projecteuler.net/problem=225
//Tribonacci Non-divisors

#include <stdio.h>
#define N 124

int nondivisor(int n) {
    //checks if n is a tribonacci nondivisor
    //just compute T_k mod n until 1,1,1 repeats. if 0 never appears then it is a nondivisor
    int a = 1; int b = 1; int c = 1;
    do {
        int tmpb = b; int tmpc = c;
        c = (a+b+c)%n; b = tmpc; a = tmpb;
        if (c == 0) return 0;
    } while (a!=1 || b!=1 || c!=1);
    return 1;
}

int main(void) {
    int n = N;
    int k = 25;
    while (n) {
        k+=2;
        if (nondivisor(k)) n--;
    }
    printf("%d\n", k);
    return 0;
}