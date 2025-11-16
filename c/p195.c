//https://projecteuler.net/problem=195
//60-degree Triangle Inscribed Circles

#include <stdio.h>
#define N 1053779
#define rt3 1.732050807568877293527446341505872366942805253

long gcd(long a, long b) {
    while (b) {
        long tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

int main(void) {
    //using the cosine rule, 60 degree triangles satisfy a^2 + b^2 - ab = c^2 for integers a,b,c.
    //the formula for inradius is A/s where A is area and s is semiperimeter. if angle between a and b is
    //60, area is just 1/2 * ab * sin(60) = sqrt(3)ab/4. s = (a+b+c)/2. Thus r = ab*sqrt3/(2(a+b+c))
    //a^2 + b^2 - ab = c^2
    //=> (a/c)^2 + (b/c)^2 - (a/c)(b/c) = 1
    //Let a/c = x; b/c = y
    //=> x^2 + y^2 - xy = 1 for rationals x,y
    //=> (x,y) are rational points on an ellipse.
    //We find these points using an algebraic geometry method.
    //Notice that (0,1) lies on the ellipse.
    //Consider the line with rational slope t passing through (0,1).
    //Its second point of intersection must also be rational.
    //It can be proven that the set of these points of intersection is identical to the set of all rational
    //points on the ellipse.
    //=> x^2 + y^2 - xy = 1; y = tx+1
    //=> x^2 + t^2 x^2 + 2xt + 1 - tx^2 - x = 1
    //=> (t^2 - t + 1) x^2 + (2t-1)x = 0
    //=> x = (1-2t)/(t^2 - t + 1)
    //=> y = (1-t^2)/(t^2 - t + 1) for some rational number t.
    //let t = p/q for coprime integers p,q.
    //=> primitive solutions to a^2 + b^2 - ab = c^2 are all of the form:
    //      a = 2pq - q^2, b = p^2 - q^2, c = p^2 - pq + q^2 for some integers p,q.
    //we simply remove duplicates and find all primitive solutions and then add the number of times this
    //primitive triangle can be scaled to keep the radius within bounds.

    double LIMIT = (double) 2*rt3*N/3;
    long ans = 0;
    for (int p = 1; p<=3*LIMIT; p++) {
        for (int q = 1; q<=6*LIMIT/p; q++) {
            //by experimentation i found that the max value of q seems to be inversely proportional to p.
            if (gcd(p,q) > 1) continue;
            long a = (long) 2*p*q - (long) q*q;
            long b = (long) p*p - (long) q*q;
            long c = (long) p*p - (long) p*q + (long) q*q;
            if (a<=0 || b<=0 || c<=0 || a>=b) continue;
            long g = gcd(a,b);
            if (g != 1 && g != 3) continue;
            if (g == 3) {
                a /= 3; b/=3; c/=3;
            }
            double r = q*(p-q);
            if (g == 3) r/=3;
            ans += LIMIT/r;
        }
    }
    printf("%ld\n", ans);
    return 0;
}