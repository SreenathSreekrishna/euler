//https://projecteuler.net/problem=131
//Prime Cube Partnership

#include <stdio.h>
#include <math.h>

int main(void) {
    //if n^3 + pn^2 = (n+k)^3, k can be proven to be a perfect square
    int isPrime[1000001] = {0};
    int cnt = 0;
    for (long i = 2; i <= 1000000; i++) {
        if (isPrime[i] == 0) {
            for (long j = 1; 3*j*j < i; j++) {
                long k = j*j;
                long n = ( k*sqrt(k*(4*i-3*k))+3*k*k)/(2*i-6*k);
                if (n<=0) continue;
                if ((3*k-i)*n*n+3*k*k*n+k*k*k) continue;
                cnt++;
            }
            for (long j = i * 2; j <= 1000000; j += i) {
                isPrime[j] = 1;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}