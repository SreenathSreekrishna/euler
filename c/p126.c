//https://projecteuler.net/problem=126
//Cuboid Layers

#include <stdio.h>
#include <math.h>

int C(int n) {
    int s = 0;
    if (n%2 == 1) return 0;
    //count number of A>=B>=C>=k such that AB+BC+CA= n/2 + k^2 - 1, where k is a positive integer
    for (int k = 1; k<sqrt(n-2) / 2; k++) {
        int t = n/2 + k*k - 1;
        for (int B = k; B <= t/k; B++) {
        for (int A = k; A<=(t-k*B)/(B+k); A++) {
            int C = (t - A*B)/(A+B);
            if (!(A>=B && B>=C && C>=k)) continue;
            s += (A*B+B*C+C*A == t);
        }}
    }
    return s;
}

int main(void) {
    int n = 10;
    while (C(n) != 1000) n+=2;
    printf("%d\n", n);
    return 0;
}