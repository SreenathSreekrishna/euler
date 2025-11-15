// //https://projecteuler.net/problem=192
// //Best Approximations

#include <stdio.h>
#include <math.h>
#define ui128 __uint128_t
#define i128 __int128_t
#define N 100000
#define BOUND 1000000000000LL

int perfectSquare(int n) {
    int s = sqrt(n);
    return s*s == n;
}

int main(void) {
    //these approximations can just be done using continued fractions.
    //we compute the continued fraction of sqrt(n) until denominator is greater than limit.
    //we take the previous fraction and compute (p+m*prevp)/(q+m*prevq) for some integer m until the 
    //denominator is just less than the bound. this is called a semiconvergent to the irrational, and 
    //it has been proven that all minima (best approximations with denominator bound) lie within the 
    //semiconvergents. we compute this for all m within bounds and choose the semiconvergent with the
    //smallest difference as our answer.
    //i also found that i cant rely on long doubles also for comparisons between semiconvergents because
    //the differences are too small. thus i use only integer arithmetic. if i have two semiconvergents
    //p1/q1 and p2/q2, comparing their differences with sqrt(n) is equivalent to comparing D1*q2*q2
    //and D2*q1*q1; where D1, D2 are pellian-type differences, being |p1^2 - n*q1^2| and |p2^2 - n*q2^2|

    long ans = 0;
    for (int n = 2; n <= N; n++) {
        if (perfectSquare(n)) continue;
        int cf[2000], len = 0;
        int start = sqrt(n), a = start, v = 0, d = 1;
        do {
            v = d*a - v;
            d = (n - v*v)/d;
            a = (start + v)/d;
            cf[len++] = a;
        } while (a != 2*start);

        long pm2 = 0, qm2 = 1;
        long pm1 = 1, qm1 = 0;
        int k = 0, lasta = 0;
        while (1) {
            long ak = (k == 0 ? start : cf[(k-1)%len]);
            ui128 qn = (ui128)ak*qm1 + qm2;
            if (qn > BOUND) { lasta = ak; break; }
            long pn = ak*pm1 + pm2;
            long qn2 = ak*qm1 + qm2;
            pm2 = pm1; qm2 = qm1;
            pm1 = pn; qm1 = qn2;
            k++;
        }

        ui128 bestD;
        long bestq = qm1;
        i128 t = (i128)pm1*pm1 - (i128)n*( (i128)qm1*qm1 );
        bestD = (t<0 ? -t : t);
        for (long r = 1; r <= a; r++) {
            ui128 P = (ui128) pm2 + (ui128) r*pm1;
            ui128 Q = (ui128) qm2 + (ui128) r*qm1;
            if (Q > BOUND) break;
            i128 t = (i128) P*P - (i128) n * ((i128)Q*Q);
            ui128 D = (t<0 ? -t : t);
            ui128 lhs = D * bestq * bestq;
            ui128 rhs = bestD * Q * Q;
            if (lhs < rhs) {
                bestD = D;
                bestq = Q;
            }
        }

        ans += bestq;
    }

    printf("%ld\n", ans);
    return 0;
}
