//https://projecteuler.net/problem=193
//Squarefree Numbers

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    //by doing some searching, i found that Q(x) = sum of mu(d)*floor(x/d^2) over d<=sqrt(x)
    //where Q(x) is the number of squarefree integers <=x and mu(d) is the mobius function, which can
    //be computed using a sieve method.
    int limit = 1L << 25;
    int *mu = calloc(limit+1, sizeof(int));
    for (int i = 0; i<=limit; i++) mu[i] = 1;
    for (int i = 2; i*i <= limit; i++)
        if (mu[i] == 1) {
            for (int j = i; j <= limit; j += i) mu[j] *= -i;
            for (int j = i * i; j <= limit; j += i * i) mu[j] = 0;
        }
    for (int i = 2; i<=limit; i++) {
        if (mu[i] == i) {
            mu[i] = 1;
        } else if (mu[i] == -i) {
            mu[i] = -1;
        } else if (mu[i] < 0) {
            mu[i] = 1;
        } else if (mu[i] > 0) {
            mu[i] = -1;
        }
    }
    long ans = 0;
    for (int d = 1; d <= limit; d++)
        ans += mu[d]*((long) limit*limit / ((long) d*d));
    
    printf("%ld\n", ans);
    free(mu);
    return 0;
}