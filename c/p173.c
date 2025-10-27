//https://projecteuler.net/problem=173
//Hollow Square Laminae I

#include <stdio.h>

int main(void) {
    //Notice that the area of a lamina is just a^2 - b^2 for some integers a,b that share parity
    //for eg. 32 = 6^2 - 2^2 = 9^2 - 7^2 = 2*16 = 4*8
    //Thus, the number of ways for n is just number of factors < sqrt(n) such that f,n/f both even
    int ans = 0;
    for (int i = 4; i<=1000000; i+=4) {
        for (int f = 2; f*f < i; f+=2) {
            if (i%f) continue;
            if (i/f % 2) continue;
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}