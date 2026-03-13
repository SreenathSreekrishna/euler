//https://projecteuler.net/problem=260
//Stone Game

#include <stdio.h>
#define N 1000

unsigned char winning[N+1][N+1][N+1] = {0};

typedef struct config {
    int a;
    int b;
    int c;
} config;

void set(int a, int b, int c) {
    if (a > N || b > N || c > N) return;
    int x,y,z;
    if (a <= b) {
        if (b <= c) {x=a; y=b; z=c;}
        else if (a <= c) {x=a; y=c; z=b;}
        else {x=c; y=a; z=b;}
    }
    else {
        if (a <= c) {x=b;y=a;z=c;}
        else if (b <= c) {x=b;y=c;z=a;}
        else {x=c;y=b;z=a;}
    }
    winning[x][y][z] = 1;
}

int main(void) {
    long ans = 0;
    for (int i = 0; i<=N; i++)
    for (int j = i; j<=N; j++)
    for (int k = j; k<=N; k++) {
        if (winning[i][j][k]) continue;
        for (int l = 1; l<=N; l++) {
            set(i+l,j,k);
            set(i,j+l,k);
            set(i,j,k+l);
            set(i+l,j+l,k);
            set(i,j+l,k+l);
            set(i+l,j,k+l);
            set(i+l,j+l,k+l);
        }
        ans += (i+j+k);
    }
    printf("%ld\n" ,ans);
    return 0;
}