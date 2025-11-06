//https://projecteuler.net/problem=182
//RSA Encryption

#include <stdio.h>
#include <stdlib.h>
#define p 1009
#define q 3643

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a%b);
}

int main(void) {
    //for every 1<e<phi (gcd(e,phi)=1), we need to find the # of m such that m^e = m mod n.
    //and then sum all e that reach the minimum count.
    //m^e = m mod n => m(m^(e-1) - 1) = 0 mod n.
    // => p | m, q | m^(e-1) - 1; q | m, p | m^(e-1) - 1; pq | m^(e-1) - 1
    //so m=0 mod p or q, m^(e-1) = 1 mod q or p; OR m^(e-1) = 1 mod pq
    //then number of possibilities in C1 is gcd(e-1, q-1) using primitive roots.
    //similarly it is gcd(e-1,p-1) for C2 by symmetry.
    //For C3, we need to count 0<m<n with m^(e-1) = 1 mod n=pq.
    //By crt this is just the product of C1 and C2.
    
    int phi = (p-1)*(q-1);
    int *unconcealed = calloc(phi,sizeof(int));
    int min = __INT_MAX__;
    for (int e = 1; e<phi; e++) {
        if (gcd(e,phi) > 1) continue;
        int a = gcd(e-1,p-1);
        int b = gcd(e-1,q-1);
        int v = a*b+a+b;
        if (v < min) {
            min = v;
        }
        unconcealed[e] = v;
    }

    long ans = 0;
    for (int e = 1; e<phi; e++)
        if (unconcealed[e] == min) ans += e;

    printf("%ld\n", ans);
    free(unconcealed);
    return 0;
}