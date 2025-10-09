//https://projecteuler.net/problem=154
//Exploring Pascal's Pyramid

#include <stdio.h>
#define N 200000

int v2(int n) {
    //v2(n!)
    int v = 0;
    while (n>0) {
        n /= 2;
        v += n;
    }
    return v;
}

int v5(int n) {
    //v5(n!)
    int v = 0;
    while (n>0) {
        n /= 5;
        v += n;
    }
    return v;
}

int main(void) {
    //# of coefficients of (x+y+z)^N divisible by 10^12
    // = # of N!/(a!b!c!) divisible by 10^12
    // => v5(N) >= v5(a) + v5(b) + v5(c) + 12 and v2(N) >= v2(a) + v2(b) + v2(c) + 12
    int l5 = v5(N)-12;
    int l2 = v2(N)-12;
    long ans = 0;
    int memo5[N+1] = {0};
    int memo2[N+1] = {0};
    for (int i = 0; i<=N; i++) {
        memo5[i] = v5(i);
        memo2[i] = v2(i);
    }
    for (int a = 0; a<=N; a++) {
        for (int b = a; a+2*b<=N; b++) {
            int c = N-a-b;
            if (memo5[a]+memo5[b]+memo5[c] > l5 || memo2[a]+memo2[b]+memo2[c] > l2) continue;
            if (a == b && b == c) ans++;
            else if (a == b || b == c) ans += 3;
            else ans += 6;
        }
    }
    printf("%ld\n", ans);
    return 0;
}