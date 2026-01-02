//https://projecteuler.net/problem=241
//Perfection Quotients

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LIMIT 1e18
#define SIEVE 1000000
#define i128 __uint128_t

int *primes;
int numPrimes = 0;
i128 ans = 0;

i128 gcd(i128 a, i128 b) {
    while (b) {
        i128 t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void dfs(i128 n, i128 num, i128 den) {
    if (n * num > LIMIT) return;
    if (gcd(n, den) != 1) return;
    if (num == 1 && den == 1) ans += n;
    if (den == 1) return;

    //find least prime factor of denominator
    int p;
    for (int i = 0; i < numPrimes; i++) {
        p = primes[i];
        if (p * p > den) {
            p = den;
            break;
        }
        if (den % p == 0) break;
    }

    //find e = vp(den)
    int e = 1;
    i128 pn = p;
    while (1) {
        i128 pn1 = pn * p;
        if (den % pn1 == 0){
            e++;
            pn = pn1;
        } else break;
    }

    for (int i = e; i < 30; i++) {
        i128 pi = pow(p, i);
        i128 newn = n*pi;
        if (newn > LIMIT) break;
        i128 newnum = num * pi;
        i128 factor = (pi*p-1) / (p-1);
        i128 newden = den * factor;
        i128 g = gcd(newnum, newden);
        newnum /= g;
        newden /= g;
        dfs(newn, newnum, newden);
    }
}

int main(void) {
    //the way i solve this problem is by running a dfs to find possible paths that can lead
    //to a particular perfection quotient. did a lot of guess and check because i also found
    //that n had to be highly divisible so i obviously did not search all primes below 10^18.
    //had to adjust some values but it eventually gave me the correct answer.

    int s = sqrt(SIEVE);
    unsigned char *IS_PRIME = calloc(s+101, sizeof(unsigned char));
    primes = calloc(2.2*(double) s/log(SIEVE), sizeof(int));
    for (int p = 2; p<=s+100; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<=s+100; j++)
                IS_PRIME[p * j]= 1;
            primes[numPrimes++] = p;
        }
    }
    free(IS_PRIME);

    for (int i = 3; i < 13; i += 2) dfs(1, i, 2);

    printf("%lld\n", (long long) ans);

    free(primes);
    return 0;
}
