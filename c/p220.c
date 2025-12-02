//https://projecteuler.net/problem=220
//Heighway Dragon

#include <stdio.h>
#define N 50
#define STEPS 1000000000000LL

typedef struct Transformation {
    int rot;
    long long dx;
    long long dy;
} Transformation;

Transformation D[N+1];
Transformation Dp[N+1];
Transformation z;
unsigned long long L[N+1];

Transformation compose(Transformation a, Transformation b) {
    Transformation t;
    switch (a.rot) {
        case 0: t.dx = a.dx + b.dx; t.dy = a.dy + b.dy; break;
        case 1: t.dx = a.dx - b.dy; t.dy = a.dy + b.dx; break;
        case 2: t.dx = a.dx - b.dx; t.dy = a.dy - b.dy; break;
        case 3: t.dx = a.dx + b.dy; t.dy = a.dy - b.dx; break;
        default: t.dx = a.dx + b.dx; t.dy = a.dy + b.dy; break;
    }
    t.rot = (a.rot + b.rot) % 4;
    return t;
}

Transformation prefix_y(int n, long long k);

Transformation prefix_x(int n, long long k) {
    if (n == 1) return D[1];
    if (k <= L[n-1]) return prefix_x(n-1, k);
    else return compose(D[n-1], prefix_y(n-1, k - L[n-1]));
}

Transformation prefix_y(int n, long long k) {
    if (n == 1) return Dp[1];
    if (k <= L[n-1]) return prefix_x(n-1, k);
    else return compose(compose(D[n-1], z), prefix_y(n-1, k - L[n-1]));
}

int main(void) {
    //Let us name the two units FRFR=x and FLFR=y. let a transformation rotating 180deg be z. then we can
    //write D1=x,D2=xy,D3=xyxzy,D4=xyxzyxyzxzy ... at each stage, x->xy; y->xzy.
    //x and y both increase number of steps by 2.
    //to get the position after STEPS steps, we need to compose the first STEPS/2 xs/ys in D_n.
    //for example, to get position after 8 steps in D_4, we compute the composition of the first 4 xs/ys
    //in xyxzyxyzxzy, which is xyxzy -> 2,-2. we can do this using just composition of previous Ds
    //and Dprimes using recursion.

    z = (Transformation){2, 0, 0}; //180 rotation
    D[1]  = (Transformation){2, 1, 1}; //FRFR
    Dp[1] = (Transformation){0, -1, 1}; //FLFR

    //L[n] = no. of x/y symbols in D[n] = 2^(n-1)
    L[1] = 1;
    for (int i = 2; i <= N; i++) L[i] = L[i-1] * 2;

    for (int i = 2; i <= N; i++) {
        D[i]  = compose(D[i-1], Dp[i-1]);
        Dp[i] = compose(compose(D[i-1], z), Dp[i-1]);
    }
    long long k = STEPS/2;
    Transformation result = prefix_x(N, k);
    printf("%lld,%lld\n", result.dx, result.dy);
    return 0;
}
