//https://projecteuler.net/problem=218
//Perfect Right-angled Triangles

#include <stdio.h>
#include <math.h>
#define BOUND 1e16

long long gcd(long long a, long long b) {
    while (b) {
        int tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

int main(void) {
    //if a,b,c is a primitive pythagorean triple with c perfect square, using the general form we
    //see that sqrt(c) must also be the hypotenuse of a primitive pythagorean triple.
    //a,b,k^2; k^2 = m^2 + n^2; k=p^2 + q^2; m=2pq; n=p^2 - q^2. 
    //for eg. 7,24,25; 25=5^2 = 3^2 + 4^2.
    //thus c=(m^2+n^2)^2 for coprime m,n
    //c <= BOUND => m,n <= sqrt(sqrt(bound))
    long long LIM = sqrtl(sqrtl(BOUND));
    long ans = 0;
    for (int i = 1; i<LIM; i++) {
        for (int j = 1; j<i; j++) {
            if (gcd(i,j) > 1) continue;
            long long m = (long long) i*i - (long long) j*j;
            long long n = (long long) 2*i*j;
            long long o = (long long) i*i + (long long) j*j;
            long long c = o*o;
            long long a = 2*m*n;
            long long b = m*m - n*n; if (b<0) b=-b;
            if (m<0 || n<0 || o<0 || o*o>BOUND) break;
            if (c>BOUND || a<0 || b<0 || c<0) break;
            if (gcd(m,n) > 1) continue;
            if (gcd(a,b) > 1) continue;
            if ((a%3 == 0 || b%3 == 0) && (a%7 == 0 || b%7 == 0) && (a/2 % 4 == 0 || b%4 == 0 || (a/2 % 2 == 0 && b%2 == 0))) continue;
            ans++;
        }
    }
    printf("%ld\n", ans);
    return 0;
}