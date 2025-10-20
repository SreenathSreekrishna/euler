//https://projecteuler.net/problem=163
//Cross-hatched Triangles

#include <stdio.h>
#include <math.h>
#define N 36

typedef struct Line {
    double x1;
    double y1;
    double x2;
    double y2;
} Line;

void printline(Line l) {
    printf("(%f %f) to (%f %f)\n", l.x1, l.y1, l.x2, l.y2);
}

int abs(int n) {
    if (n<0) return -n;
    return n;
}

int isTriangle(Line a, Line b, Line c) {
    Line arr[3] = { a, b, c };
    double px[3], py[3];
    int pairs[3][2] = { {0,1}, {1,2}, {2,0} };
    for (int idx = 0; idx < 3; ++idx) {
        int i = pairs[idx][0], j = pairs[idx][1];
        double x1 = arr[i].x1, y1 = arr[i].y1, x2 = arr[i].x2, y2 = arr[i].y2;
        double x3 = arr[j].x1, y3 = arr[j].y1, x4 = arr[j].x2, y4 = arr[j].y2;
        double denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
        //parallel
        if (fabs(denom) < 1e-9) return 0;

        double numx = (x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4);
        double numy = (x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4);
        double ix = numx / denom;
        double iy = numy / denom;
        //intersection lies inside region
        double minx1 = fmin(x1, x2) - 1e-9, maxx1 = fmax(x1, x2) + 1e-9;
        double miny1 = fmin(y1, y2) - 1e-9, maxy1 = fmax(y1, y2) + 1e-9;
        double minx2 = fmin(x3, x4) - 1e-9, maxx2 = fmax(x3, x4) + 1e-9;
        double miny2 = fmin(y3, y4) - 1e-9, maxy2 = fmax(y3, y4) + 1e-9;
        if (!(ix >= minx1 && ix <= maxx1 && iy >= miny1 && iy <= maxy1 &&
              ix >= minx2 && ix <= maxx2 && iy >= miny2 && iy <= maxy2)) {
            return 0;
        }
        px[idx] = ix;
        py[idx] = iy;
    }

    double x1 = px[0], y1 = py[0];
    double x2 = px[1], y2 = py[1];
    double x3 = px[2], y3 = py[2];
    double area2 = fabs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
    if (area2 < 1e-9) return 0;
    return 1;
}


int main(void) {
    //this problem can just be solved using bruteforce and coordinate bashing
    //all lines have either 0,30,60,90,120 or 150 degree angles with horizontal
    Line lines[1024];
    int numLines = 0;
    int K = 2*N-1;
    double rt3 = sqrt(3);
    Line l;
    for (int i = 0; i<N; i++) {
        l.x1 = i; l.y1 = 0;
        l.x2 = (double) (N+i) / 2; l.y2 = rt3*(N-i)/2;
        lines[numLines++] = l;
        l.x1 = (double) i / 2; l.y1 = rt3 * i / 2;
        l.x2 = (double) (2*N-i) / 2; l.y2 = rt3 * i / 2;
        lines[numLines++] = l;
        l.x1 = N-i; l.y1 = 0;
        l.x2 = (double) (N-i) / 2; l.y2 = rt3*(N-i)/2;
        lines[numLines++] = l;
    }
    for (int i = 1; i<=K; i++) {
        l.x1 = (double) i / 2; l.y1 = 0;
        l.x2 = (double) i / 2; l.y2 = (double) (N-abs(N-i)) * rt3 / 2;
        lines[numLines++] = l;
        l.x1 = (double) i / 4; l.y1 = rt3 * i / 4;
        l.x2 = l.x1 + (double) (N-abs(N-i)) * 3 / 4; l.y2 = l.y1 - (double) (N-abs(N-i)) * rt3 / 4;
        lines[numLines++] = l;
        l.x1 = (double) N - (double) i / 4;
        l.x2 = l.x1 - (double) (N-abs(N-i)) * 3 / 4;
        lines[numLines++] = l;
    }

    int ans = 0;
    for (int i = 0; i<numLines; i++)
    for (int j = i+1; j<numLines; j++)
    for (int k = j+1; k<numLines; k++)
        ans += isTriangle(lines[i], lines[j], lines[k]);
    
    printf("%d\n", ans);
    return 0;
}