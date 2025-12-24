//https://projecteuler.net/problem=236
//Luxury Hampers

#include <stdio.h>
#include <math.h>

typedef struct frac {
    long p;
    long q;
} frac;

long gcd(long a, long b) {
    long tmp;
    while (b) {
        tmp = a;
        a = b;
        b = tmp%b;
    }
    return a;
}

frac reduce(frac x) {
    long g = gcd(x.p,x.q);
    x.p /= g;
    x.q /= g;
    return x;
}

long isSquare(long x) {
    long s = sqrt(x);
    if (s*s == x) return s; else return 0;
}

int fracGreater(frac x, frac y) {
    //checks if x>y
    return y.q*x.p > x.q*y.p;
}

int main(void) {
    //let number of spoiled products for A and B be a,b,c,d,e and p,q,r,s,t respectively. 
    //The problem states that:
    //p/640 = ma/5248, q/1888 = mb/1312, r/3776 = mc/2624, s/3776 = md/5760, t/5664 = me/3936
    //and finally that (a+b+c+d+e)/18880 = m(p+q+r+s+t)/15744.
    int cnt = 1;
    frac max = {0,1};
    for (long x = 59; x<5248; x+=59)
    for (long y = 41; y<1312; y+=41)
    for (long z = 5; z<2624; z+=5) {
        frac m2 = reduce((frac) {(x+y+z)*108*41*41, (450*x+90*59*y+41*59*z)*59});
        frac m = {isSquare(m2.p), isSquare(m2.q)};
        if (m.p && m.q) if (fracGreater(m, max)) max = m;
    }
    printf("%ld/%ld\n", max.p, max.q);
    return 0;
}