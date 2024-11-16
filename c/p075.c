//https://projecteuler.net/problem=75
//Singular Integer Right Triangles

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 1500000

int gcd(int a, int b) {
    if (a == b) {
        return a;
    }
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    if (b>a) {
        return gcd(a,b % a);
    }
    if (a>b) {
        return gcd(b,a % b);
    }
    return 1;
}

int main(void) {
    //the sum of sides of integer sided right triangles are always
    //of the form 2ac(a+b) for a>b; from the general form for pythagorean triples

    int numWays[N+1] = {0};
    int ***triplets = malloc(sizeof(int**)*(N+1));
    for (int i = 0; i<=N; i++) {
        triplets[i] = malloc(sizeof(int*)*6);
        for (int j = 0; j<6; j++) {
            triplets[i][j] = malloc(sizeof(int)*3);
            for (int k = 0; k<3; k++) triplets[i][j][k] = 0;
        }
    }

    for (int c = 1; c<=N/2; c++) {
        //a(a+b) <= 750000/c
        for (int b = 1; b<=((int) (N/2/c)+1); b++) {
            int amax = (sqrt(b*b+2*(float)N/c)-b)/2+1;
            for (int a = b+1; a<=amax; a++) {
                int v = 2*a*c*(a+b);
                if (gcd(a,b) != 1 || v > N || v<0) {
                    continue;
                }
                int x = c*(a*a-b*b);
                int y = 2*a*b*c;
                int z = c*(a*a+b*b);
                if (numWays[v] < 6) {
                    triplets[v][numWays[v]][0] = x;
                    triplets[v][numWays[v]][1] = y;
                    triplets[v][numWays[v]][2] = z;
                }
                numWays[v]++;
            }
        }
    }

    int num = 0;
    for (int i = 0; i<=N; i++) {
        if (numWays[i] > 2 && numWays[i]) {
            continue;
        }
        if (numWays[i] == 1) {
            num++;
        }
        if (numWays[i] == 2) {
            if (triplets[i][0][1] != triplets[i][1][0]
             || triplets[i][0][0] != triplets[i][1][1]) {
                continue;
            }
            num++;
        }
    }
    printf("%d\n",num);
    for (int i = 0; i<=N; i++) {
        for (int j = 0; j<6; j++) {
            free(triplets[i][j]);
        }
        free(triplets[i]);
    }
    free(triplets);
}