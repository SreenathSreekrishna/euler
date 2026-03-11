//https://projecteuler.net/problem=257
//Angular Bisectors

#include <stdio.h>
#define LIMIT 100000000

long gcd(long a, long b) {
    long tmp;
    while (b) {
        tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

int main(void) {
    //by using the angle bisector theorem and similar triangles, it is possible to prove that
    //the ratio of the areas mentioned is (x+y)(x+z)/(yz) if the sides of the triangle are
    //x,y,z. Thus, we must solve the diophantine (x+y)(x+z)=kyz for positive integers x,y,z,k
    //Notice that k must be 2,3, or. 4. this can be proven using the triangle inequality and
    //simplifying using our equation. the only way k=4 is if the triangle is equilateral and
    //x=y=z. thus we only need to check k=2 and k=3.
    //we can simplify by taking the gcd of x and y and putting x=da, y=db. we do this because
    //we can easily notice that similar triangles will all follow the rule if one of them works.
    //then, we get the equation tz = ad(a+b), where t = (k-1)b-a. we can get primitive solutions
    //using this and add up. we just need to bound a,b based on the inequalities to optimize.
    long ans = LIMIT / 3; //for k=4
    for (long k = 2; k<=3; k++) {
        for (long b = 1; b<=42000; b++) {
            for (long a = 1; 2*a<=(k-1)*b && a<=b; a++) {
                if (gcd(a,b) != 1) continue;
                long t = (k-1) * b - a;
                long g = gcd(t, a*(a+b));
                long x0 = a*t/g;
                long y0 = b*t/g;
                long z0 = a*(a+b)/g;
                if (x0 + y0 <= z0 || y0 + z0 <= x0 || z0 + x0 <= y0 || x0+y0+z0>LIMIT || z0>y0) continue;
                ans += (LIMIT / (x0+y0+z0));
            }
        }
    }
    printf("%ld\n", ans);
    return 0;
}