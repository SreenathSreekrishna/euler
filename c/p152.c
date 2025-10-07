//https://projecteuler.net/problem=152
//Sums of Square Reciprocals

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

typedef __int128 i128;

typedef struct {
    i128 p;
    i128 q;
} frac;

i128 i128_abs(i128 x) { return x < 0 ? -x : x; }

i128 gcd_i128(i128 a, i128 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        i128 r = a % b;
        a = b;
        b = r;
    }
    return a;
}

frac make_frac(i128 p, i128 q) {
    frac f;
    if (q < 0) { p = -p; q = -q; }
    if (p == 0) {
        f.p = 0;
        f.q = 1;
        return f;
    }
    i128 g = gcd_i128(i128_abs(p), i128_abs(q));
    p /= g; q /= g;
    f.p = p; f.q = q;
    return f;
}

frac frac_add(frac *a, frac *b) {
    frac r;
    i128 p = a->p * b->q + a->q * b->p;
    i128 q = a->q * b->q;
    if (p == 0) { r.p = 0; r.q = 1; return r; }
    i128 g = gcd_i128(i128_abs(p), i128_abs(q));
    r.p = p / g;
    r.q = q / g;
    return r;
}

frac frac_sub(frac *a, frac *b) {
    frac r;
    i128 p = a->p * b->q - a->q * b->p;
    i128 q = a->q * b->q;
    if (p == 0) { r.p = 0; r.q = 1; return r; }
    i128 g = gcd_i128(i128_abs(p), i128_abs(q));
    r.p = p / g;
    r.q = q / g;
    return r;
}

int cmp_half(frac *a) {
    // compare 2*a.p with a.q
    i128 lhs = a->p * 2;
    i128 rhs = a->q;
    if (lhs < rhs) return -1;
    if (lhs == rhs) return 0;
    return 1;
}

int possible_list[] = {
    2,3,4,5,6, 7,8,9,10,12,
    13,14,15,16,18, 20,21,24,27,28,
    30,32,35,36,39, 40,42,45,48,52,
    54,56,60,63,64, 65,70,72,80
}; //found this list by looking for optimizations online. completely missed this approach. this is the list of values that the denominators can take.

int M = sizeof(possible_list)/sizeof(possible_list[0]);

frac tfrac[64];
double tdbl[64];
double sufApprox[64];

int sol = 0;
int stack_vals[128];

void solve(int start, int depth, frac *target, frac *curSum, double curApprox) {
    if (curApprox > 0.5 + 1e-15) return;
    if (target->p == 0) sol++;
    if (start >= M) return;
    if (curApprox + sufApprox[start] + 1e-15 < 0.5) return;
    for (int idx = start; idx < M; idx++) {
        double nxtApprox = curApprox + tdbl[idx];
        if (nxtApprox > 0.5 + 1e-15) continue;
        frac newSum = frac_add(curSum, &tfrac[idx]);
        if (cmp_half(&newSum) > 0) continue;
        frac newTarget = frac_sub(target, &tfrac[idx]);
        stack_vals[depth] = possible_list[idx];
        solve(idx + 1, depth + 1, &newTarget, &newSum, nxtApprox);
    }
}

int main(void) {
    for (int i = 0; i < M; i++) {
        int n = possible_list[i];
        i128 p = 1;
        i128 q = (i128)n * (i128)n;
        tfrac[i] = make_frac(p, q);
        tdbl[i] = 1.0 / ((double)n * (double)n);
    }

    sufApprox[M-1] = tdbl[M-1];
    for (int i = M-2; i >= 0; i--) sufApprox[i] = sufApprox[i+1] + tdbl[i];

    frac target = make_frac(1, 2);
    frac zero = make_frac(0, 1);
    frac cur = make_frac(0,1);

    solve(0, 0, &target, &cur, 0.0);

    printf("%d\n", sol);
    return 0;
}