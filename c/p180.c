//https://projecteuler.net/problem=180
//Golden Triplets

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define i128 __int128_t
#define N 35

typedef struct frac {
    i128 p;
    i128 q;
} frac;

i128 gcd(i128 a, i128 b) {
    if (!b) return a;
    return gcd(b,a%b);
}

frac reduce(frac f) {
    i128 g = gcd(f.p, f.q);
    return (frac){ f.p/g, f.q/g };
}

frac fracadd(frac a, frac b) {
    return reduce((frac) {(i128) a.p*b.q + a.q*b.p, (i128) a.q*b.q});
}

frac fracmult(frac a, frac b) {
    return reduce((frac) {a.p*b.p, a.q*b.q});
}

int fraccmp(const void *a, const void *b) {
    const frac *m = a, *n = b;
    i128 v =  (i128) m->p * n->q - (i128) n->p * m->q;
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

int golden(frac x, frac y, frac z) {
    frac s = fracadd(x,y);
    if (fraccmp(&s, &z) == 0) return 1;
    frac sqs = fracadd(fracmult(x,x),fracmult(y,y));
    frac sq = fracmult(z,z);
    if (fraccmp(&sqs,&sq) == 0) return 2;
    return 0;
}

frac fracsq(frac x) {
    //tests if x is a perfect square (as a fraction)
    i128 a = sqrt(x.p);
    i128 b = sqrt(x.q);
    if (!(a*a == x.p && b*b == x.q)) return (frac) {0,0};
    return (frac) {a,b};
}

frac inv(frac f) {
    return (frac) {f.q, f.p};
}

frac goldenSums[100000];
int sumsLen = 0;

void addsums(frac x, frac y) {
    //finds all golden sums for this pair of x,y and adds it to the list
    //n = 1
    frac z = fracadd(x,y);
    frac sum = z;
    if (z.p <= N && z.q <= N && z.p < z.q) goldenSums[sumsLen++] = fracadd(z,z);
    //n=2
    frac z2 = fracadd(fracmult(x,x),fracmult(y,y));
    z = fracsq(z2);
    if (z.p <= N && z.q <= N && z.p < z.q && (z.p || z.q)) goldenSums[sumsLen++] = fracadd(sum, z);

    //n = -1
    z = inv(fracadd(inv(x), inv(y)));
    if (z.p <= N && z.q <= N && z.p < z.q) goldenSums[sumsLen++] = fracadd(sum,z);
    //n = -2
    z2 = inv(fracadd(fracmult(inv(x),inv(x)),fracmult(inv(y),inv(y))));
    z = fracsq(z2);
    if (z.p <= N && z.q <= N && z.p < z.q && (z.p || z.q)) goldenSums[sumsLen++] = fracadd(sum, z);
}

int main(void) {
    //notice that f_n(x,y,z) = (x+y+z)(x^n + y^n - z^n) after expanding and factoring
    //Thus, f_n(x,y,z) = 0
    // => (x+y+z)(x^n + y^n - z^n) = 0. As x,y,z > 0,
    // => x^n + y^n - z^n = 0
    // => x^n + y^n = z^n
    //If we take a common denominator, we get a^n + b^n = c^n for some integers a,b,c
    //However, due to Fermat's last theorem, there are no solutions for n>2.
    //Thus, we only have to check n=+-1 and +-2. (x+y = z OR x^2 + y^2 = z^2 (and inverses))

    frac fracs[1024];
    int numFracs = 0;
    for (int a = 1; a<=N; a++)
    for (int b = a+1; b<=N; b++) {
        if (gcd(a,b) > 1) continue;
        fracs[numFracs++] = (frac) {a,b};
    }
    qsort(fracs, numFracs, sizeof(frac), fraccmp);

    for (int i = 0; i<numFracs; i++)
    for (int j = i; j<numFracs; j++)
        addsums(fracs[i], fracs[j]);
    
    //sort golden sums to remove dupes
    qsort(goldenSums, sumsLen, sizeof(frac), fraccmp);
    
    frac ans = goldenSums[0];
    frac curr = goldenSums[0];
    for (int i = 1; i<sumsLen; i++) {
        if (fraccmp(&curr, &goldenSums[i]) == 0) continue;
        ans = fracadd(ans, goldenSums[i]);
        curr = goldenSums[i];
    }
    i128 answer = ans.p + ans.q;
    printf("%lld\n", (long long) answer);
    return 0;
}