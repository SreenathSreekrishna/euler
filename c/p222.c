//https://projecteuler.net/problem=222
//Sphere Packing

#include <stdio.h>
#include <math.h>
#define R 50

double memo[2097152][21] = {0};

double findHeightBetween(int r1, int r2) {
    double v = (double) R * ((double) r1+r2 - R);
    if (v<0) return 0;
    return 2.0F*sqrt(v);
}

double findMinHeight(int maskUsed[21], int lastUsed) {
    int mask = 0;
    for (int i = 0; i<21; i++) {
        mask*=2;
        mask+=maskUsed[i];
    }
    if (memo[mask][lastUsed-30]) return memo[mask][lastUsed-30];
    double minh = 1e10;
    int used = 0;
    for (int i = 0; i<21; i++) {
        if (maskUsed[i]) {
            used++;
            continue;
        }
        double h = findHeightBetween(i+30, lastUsed);
        if (!h) continue;
        maskUsed[i] = 1;
        h += findMinHeight(maskUsed, i+30);
        if (h<minh) minh = h;
        maskUsed[i] = 0;
    }
    if (used == 21) {
        memo[mask][lastUsed-30] = lastUsed;
        return lastUsed;
    }
    memo[mask][lastUsed-30] = minh;
    return minh;
}

int main(void) {
    //the distance between the centres of two spheres stacked inside the pipe on top of each other can be
    //calculated using the pythagorean theorem. d^2 + (2R-r1-r2)^2 = (r1+r2)^2
    // => d = 2sqrt(R(r1+r2-R))
    //now, we just run a dfs to find the min height.
    int used[21] = {0};
    used[20] = 1;
    printf("%.0f\n", 1000*(50.0+findMinHeight(used, 50)));
    return 0;
}