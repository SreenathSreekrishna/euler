//https://projecteuler.net/problem=184
//Triangles Containing the Origin

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 1e-9
#define N 105

int cmp(const void *ap, const void *bp) {
    double a = *(double *)ap; double b = *(double *)bp;
    double diff = a-b;
    if (diff > EPS) return 1;
    if (diff < -EPS) return -1;
    return 0;
}

int main(void) {
    //Notice that for triangle ABC, it contains the origin if and only if angle AOB,BOC,COA are all
    //less than 180deg. Thus, we first enumerate all points and then sort by their angle with horizontal.
    //After that, i loop over all valid pairs of points that could form a triangle maybe.
    //notice that the third point must have an angle within the sector defined by the vertically opposite
    //angle of the two points which we loop over. because of this, the number of points in that region must
    //be the same as between indexes i and j by symmetry. we just remove duplicates, (as those correspond to
    //edge cases where the origin lies on one of the sides of the triangle) and then just add all the indices 
    //between the two variables in the loop.
    //I could have maybe made this more efficient by just considering the quarter circle in the first quadrant
    //but I'm just tired of this problem at this point so dont want to do any more debugging to implement that.
    int numPoints = 0;
    double angles[40000];
    for (int i = -N; i<=N; i++)
    for (int j = -N; j<=N; j++) {
        if (!i && !j) continue;
        if (i*i+j*j >= N*N) continue;
        double angle = atan2(i,j);
        if (angle < 0) angle += 2*M_PI;
        angles[numPoints++] = angle;
    }
    qsort(angles, numPoints, sizeof(double), cmp);

    long ans = 0;

    for (int i = 0; i<numPoints; i++) {
        for (int j = i+1; j<numPoints; j++) {
            if (fabs(angles[j] - angles[i]) < EPS) continue;
            if (angles[j] - angles[i] + EPS >= M_PI) break;
            int l = i; int r = j;
            while (l<numPoints && fabs(angles[l] - angles[i]) < EPS) l++;
            while (r >= l && fabs(angles[r] - angles[j]) < EPS) r--;
            int num = r-l+1;
            ans += num;
        }
    }

    printf("%ld\n", ans/2); //remove half because of symmetry of the third point.
    return 0;
}