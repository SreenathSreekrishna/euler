//https://projecteuler.net/problem=228
//Minkowski Sums

#include <stdio.h>
#include <stdlib.h>
#define A 1864
#define B 1909

typedef struct frac {
    int p;
    int q;
} frac;

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a%b);
}

int fraccmp(const void *a, const void *b) {
    const frac *m = a, *n = b;
    int v = m->p * n->q - n->p * m->q;
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

int main(void) {
    //Let the perpendicular directions of each side from the origin be represented by fractions. for e.g.
    //S3 will have sides with directions 0/3, 1/3, 2/3 in order. for S4, it is 0/4, 1/4, 2/4, 3/4.
    //Notice that the sides with same direction merge in the minkowski sum, while those with different
    //directions do not. thus all we have to do is calculate the number of distinct fractions within the
    //range to get the answer. in the example, 0/3 and 0/4 merge, so the number of sides becomes 4+3-1=6
    frac fracs[(A+B)*(B-A+1)/2 + 1];
    int fracsLen = 0;
    for (int i = A; i<=B; i++) {
        for (int j = 0; j<i; j++) {
            int g = gcd(i,j);
            fracs[fracsLen++] = (frac) {j/g, i/g};
        }
    }
    qsort(fracs, fracsLen, sizeof(frac), fraccmp);
    int ans = 1;
    for (int i = 1; i<fracsLen; i++) if (fraccmp(&fracs[i],&fracs[i-1])) ans++;
    printf("%d\n", ans);
    return 0;
}