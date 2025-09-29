//https://projecteuler.net/problem=141
//Square Progressive Numbers

#include <stdio.h>
#include <math.h>

int main(void) {
    // q = floot(n/d); r = n%d, n = dq+r
    //C1: r^2 = dq
    //  => r^2 = n - r
    //  => r = (sqrt(4n+1)-1)/2
    //  => As n is a perfect square >0, 4n+1 is never a perfect square, so r is never an integer
    //  => There are no possible cases in C1
    //C2: d^2 = qr
    //  => d^2 / q = r < d
    //  => d/q < 1
    //  => d<q, d^2/q is an integer (q|d^2)
    //  n = dq+r > d^2 + d^2/q = d^2(1+1/q) > d^2
    //C3: q^2 = dr
    //  => q^2 / d = r < d
    //  => q<d, q^2/d is an integer (d|q^2)
    //Notice that C3 is just the same as C2 by symmetry (exchanging q and d).
    //We can switch these around like this because it can be proven that d^2<n for C2 so the
    //remainder r will still remain within bounds when switching d and q.
    //Working only with C2, we get n = d^3/r + r
    //By checking small cases, we see that r is usually highly divisible/has a large square factor
    //Let r = kt^2
    long s = 0;
    for (long d = 2; d<1000000; d++) {
        //find r<d such that r|d^2
        int found = 0;
        for (long t = sqrt(d); t>=1 && !found; t--) {
            for (long k = 1; t*t*k<d; k++) {
                long r = t*t*k;
                long q = (d*d)/r;
                long n = d*q + r;
                if (n>2000000000000) break;
                if (n>=1000000000000) continue;
                if (r>=d || (d*d)%r) continue;
                long sq = sqrt(n);
                if (sq*sq!=n) continue;
                s += n;
                found = 1;
                break;
            }
        }
    }
    printf("%ld\n", s);
    return 0;
}