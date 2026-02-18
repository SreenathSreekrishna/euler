//https://projecteuler.net/problem=255
//Rounded Square Roots

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DIGITS 14

typedef struct state {
    long x;
    long a;
    long b;
    int depth;
} state;

long ceildiv(long x, long y) {
    return (x%y == 0 ? x/y : x/y+1);
}

int main(void) {
    //i solve this problem by grouping numbers by their ceildiv. this reduces the search from 10^14
    //to only about 10^7 (its basically like the square root method thing used for factors)

    long x0 = 2+5*(1-DIGITS%2);
    for (int i = 0; i<(DIGITS-1)/2; i++) x0 *= 10;
    long A = 1;
    for (int i = 0; i<DIGITS; i++) A*=10;
    state *states = calloc(15000000, sizeof(state));
    int statesLen = 1;
    states[0] = (state) {x0, A/10, A-1, 1};
    long ans = 0;
    while (statesLen) {
        state curr = states[--statesLen];
        for (long t = ceildiv(curr.a,curr.x); t <= ceildiv(curr.b,curr.x); t++) {
            long lb = curr.x*(t-1)+1;
            long ub = curr.x*t;
            if (lb < curr.a) lb = curr.a;
            if (ub > curr.b) ub = curr.b;
            long xk = (t+curr.x)/2;
            if (xk == curr.x) {
                ans += (ub - lb + 1) * curr.depth;
            }
            else {
                states[statesLen++] = (state) {xk, lb, ub, curr.depth+1};
            }
        }
    }
    printf("%.10f\n", (double) ans / (9*A/10));

    free(states);
    return 0;
}