//https://projecteuler.net/problem=120
//Square Remainders

#include <stdio.h>

int main(void) {
    //(a-1)^n + (a+1)^n = 2a^n + 2NC2 a^(n-2) + 2NC4 a^(n-4) ...
    //(a-1)^n + (a+1)^n = 2,2a,6a,10a,14a,18a,...(4k+2)a (mod a^2)
    int s = 0;
    for (int a = 3; a<=1000; a++) {
        int n = (a-1) / 2;
        s += 2*n*a;
    }
    printf("%d\n", s);
}