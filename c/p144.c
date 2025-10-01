//https://projecteuler.net/problem=144
//Laser Beam Reflections

#include <stdio.h>

int main(void) {
    long double x1 = 0;   long double y1 = 10.1;
    long double x2 = 1.4; long double y2 = -9.6;
    int reflections = 0;
    while (x2>0.01 || x2<-0.01 || y2<0) {
        //slope of reflected line s(x-x2) + y2 (i did the math ...)
        long double s = (8*x2*y2*(x1-x2)+(y2-y1)*(16*x2*x2-y2*y2))/(-8*x2*y2*(y2-y1) + (x1-x2)*(16*x2*x2-y2*y2));
        long double newx = 2*s*(x2*s-y2)/(s*s+4) - x2;
        long double newy = s*(newx-x2) + y2;
        x1 = x2; y1 = y2;
        x2 = newx; y2 = newy;
        reflections++;
    }
    printf("%d\n", reflections);
    return 0;
}