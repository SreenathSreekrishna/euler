//https://projecteuler.net/problem=102
//Triangle Containment

#include <stdio.h>

int abs(int x) {
    if (x<0) return -x;
    return x;
}

int containsOrigin(int x1, int y1, int x2, int y2, int x3, int y3) {
    int ar = abs(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2));
    int ar1 = abs(x1*y2 - x2*y1);
    int ar2 = abs(x2*y3 - x3*y2);
    int ar3 = abs(x3*y1 - x1*y3);
    return (ar1+ar2+ar3) == ar;
}

int main(void) {
    FILE *f = fopen("../files/p102_triangles.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
    int n = 0;
    for (int i = 0; i<1000; i++) {
        int triangle[6];
        fscanf(f,"%d,%d,%d,%d,%d,%d\n",&triangle[0],&triangle[1],&triangle[2],&triangle[3],&triangle[4],&triangle[5]);
        n += containsOrigin(triangle[0],triangle[1],triangle[2],triangle[3],triangle[4],triangle[5]);
    }
    printf("%d\n", n);
    return 0;
}