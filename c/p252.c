// //https://projecteuler.net/problem=252
// //Convex Holes

// #include <stdio.h>
// #define N 20

// typedef struct Pointoint {
//     int x;
//     int y;
// } Pointoint;

// int main(void) {
//     long S = 290797;
//     Pointoint pointpoints[N];
//     for (int i = 0; i<N; i++) {
//         S = (S*S) % 50515093;
//         int x = (S%2000) - 1000;
//         S = (S*S) % 50515093;
//         int y = (S%2000) - 1000;
//         pointpoints[i] = (Pointoint) {x,y};
//     }
//     for (int i = 0; i<N; i++) {
//         printf("(%d, %d)\n", pointpoints[i].x, pointpoints[i].y);
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define N 500
#define BITS (((N)+63)/64)

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct {
    Point p;
    int idx;
} PointI;

Point pivot;
Point points[N];
//stores which points are to the left of both i and j. each long long is 64 bits so 
//i use BITS long longs to store N booleans (which tell if each point is to the left of ij or not)
long long before[N][N][BITS] = {0};

long long cross(Point a, Point b, Point c) {
    return (long long)(b.x - a.x)*(c.y - a.y) - (long long)(b.y - a.y)*(c.x - a.x);
}
double area(Point a, Point b, Point c) {
    return (double) llabs(cross(a,b,c)) * 0.5;
}

int cmp(const void *a, const void *b) {
    Point x = *(Point*) a, y = *(Point*)b;
    if (x.x > y.x) return 1;
    if (x.x < y.x) return -1;
    if (x.y > y.y) return 1;
    if (x.y < y.y) return -1;
    return 0;
}

int polarCmp(const void *A, const void *B) {
    //compares A and B by polar angle around the pivot.
    PointI a = *(PointI*)A, b = *(PointI*)B;
    long long c = cross(pivot, a.p, b.p);
    if (c>0) return -1;
    if (c<0) return 1;
    long long v1= (long long) (a.p.x-pivot.x)*(a.p.x-pivot.x)+(long long) (a.p.y-pivot.y)*(a.p.y-pivot.y);
    long long v2= (long long) (b.p.x-pivot.x)*(b.p.x-pivot.x)+(long long) (b.p.y-pivot.y)*(b.p.y-pivot.y);
    if (v1>v2) return 1;
    if (v1<v2) return -1;
    return 0;
}

int empty(int A,int B, int C) {
    //checks if triangle formed by points in indices A,B,C is empty
    for (int i = 0; i<BITS; i++) 
        if (before[A][B][i] & before[B][C][i] & before[C][A][i]) return 0;
    return 1;
}

int main(void) {
    long S = 290797;
    for (int i = 0; i<N; i++) {
        S = (S*S) % 50515093; points[i].x = (int) (S%2000)-1000;
        S = (S*S) % 50515093; points[i].y = (int) (S%2000)-1000;
    }

    //first, I sort points lexographically.
    qsort(points, N, sizeof(Point), cmp);

    //build the before binary array for faster lookup on which  triangles are empty.
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            if (i == j) continue;
            for (int k = 0; k<N; k++) {
                if (k == i || k == j) continue;
                if (cross(points[i], points[j], points[k]) > 0)
                    before[i][j][k/64] += 1ULL << (k%64);
            }
        }
    }

    double ans = 0.0;

    PointI arr[N];
    int order[N];
    unsigned char emptyTri[N][N];
    double dp[N][N];

    for (int v = 0; v < N; v++) {
        //sort the points according to their polar angle with pivot
        //im using pointI here to also preserve lexographic index in original arr
        int m = 0;
        for (int i = v+1; i<N; i++) arr[m++] = (PointI) {points[i], i};
        pivot = points[v];
        qsort(arr, m, sizeof(PointI), polarCmp);
        for (int i = 0; i<m; i++) order[i] = arr[i].idx;

        for (int i = 0; i<m; i++)
        for (int j = i+1; j<m; j++)
            emptyTri[i][j] = empty(v,order[i],order[j]);
        
        for (int i = 0; i<m; i++)
        for (int j = 0; j<m; j++)
            dp[i][j] = -1.0;
        
        //create the starting triangle
        for (int i = 0; i<m; i++)
        for (int j = i+1; j<m; j++)
            if (emptyTri[i][j]) dp[i][j] = area(points[v], points[order[i]], points[order[j]]);
        
        //choose other points in the polygon
        for (int b = 0; b<m; b++)
        for (int a = 0; a<b; a++) {
            if (dp[a][b] < 0) continue;
            for (int c = b+1; c<m; c++) {
                if(cross(points[order[a]], points[order[b]], points[order[c]]) < 0) continue;
                if(!emptyTri[b][c]) continue;
                double newarea = dp[a][b] + area(points[v], points[order[b]], points[order[c]]);
                if (newarea > dp[b][c]) {
                    dp[b][c] = newarea;
                    if (newarea > ans) ans = newarea;
                }
            }
        }
    }

    printf("%.1f\n", ans);
    return 0;
}
