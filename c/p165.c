//https://projecteuler.net/problem=165
//Intersections

#include <stdio.h>
#include <stdlib.h>
#define EPSA 1e-9
#define EPSB 1e-9

typedef struct Line {
    double x1;
    double y1;
    double x2;
    double y2;
} Line;

double fabs(double x) {
    if (x<0) return -x;
    return x;
}

int comp(const void *a, const void *b) {
    const double *A = a;
    const double *B = b;
    if (fabs(A[0] - B[0]) > EPSB)
        return (A[0] < B[0]) ? -1 : 1;
    if (fabs(A[1] - B[1]) > EPSB)
        return (A[1] < B[1]) ? -1 : 1;
    return 0;
}

double pointx;
double pointy;
double distinct[4194304][2];

int trueIntersection(Line a, Line b) {
    double x1 = a.x1, y1 = a.y1, x2 = a.x2, y2 = a.y2;
    double x3 = b.x1, y3 = b.y1, x4 = b.x2, y4 = b.y2;

    double denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if (fabs(denom) < EPSA) return 0; // parallel or coincident

    //reduce to parametric form
    double t = ((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4)) / denom;
    double u = ((x1 - x3)*(y1 - y2) - (y1 - y3)*(x1 - x2)) / denom;

    if (t <= 0 || t >= 1 || u <= 0 || u >= 1) return 0;

    double px = x1 + t * (x2 - x1);
    double py = y1 + t * (y2 - y1);

    pointx = px;
    pointy = py;
    return 1;
}


int main(void) {
    int s[20001];
    s[0] = 290797;
    for (int i = 1; i<=20000; i++) {
        s[i] = ((long) s[i-1]*s[i-1])%50515093;
    }
    Line lines[5000];
    for (int i = 0; i<5000; i++) {
        Line l;
        l.x1 = s[4*i+1]%500;
        l.y1 = s[4*i+2]%500;
        l.x2 = s[4*i+3]%500;
        l.y2 = s[4*i+4]%500;
        lines[i] = l;
    }
    int ans = 0;
    for (int i = 0; i<5000; i++) {
        for (int j = 0; j<i; j++) {
            if (!trueIntersection(lines[i],lines[j])) continue;
            distinct[ans][0] = pointx;
            distinct[ans][1] = pointy;
            ans++;
        }
    }
    qsort(distinct, ans, sizeof(double)*2, comp);
    int final = 1;
    for (int i = 0; i<ans-1; i++) {
        if (fabs(distinct[i][0] - distinct[i+1][0]) < EPSB && fabs(distinct[i][1] - distinct[i+1][1]) < EPSB) continue;
        final++;
    }
    printf("%d\n", final);
    return 0;
}