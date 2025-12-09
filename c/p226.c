//https://projecteuler.net/problem=226
//A Scoop of Blancmange

#include <stdio.h>
#include <math.h>

double s(double x) {
    double diff = x - (long) x;
    if (diff > 0.5) return 1-diff;
    return diff;
}

double blanc(double x) {
    double pow = 1;
    double ret = 0;
    for (int n = 0; n<64; n++) {
        ret += s(x*pow) / pow;
        pow *= 2;
    }
    return ret;
}

int dist(double x, double y) {
    //checks if (x,y) lies within circle or not.
    x -= 0.25;
    y -= 0.5;
    double r2 = x*x+y*y;
    if (r2 < 1.0f/16.0f) return 1;
    if (r2 > 1.0f/16.0f) return -1;
    return 0;
}

double I(double x) {
    if (x < 1e-10) return 0;
    if (x > 1.0 - 1e-10) return 0.5;
    if (x <= 0.5) return I(2*x)/4.0f + x*x/2.0f;
    else if (x <= 1) return 0.5 - I(1.0f-x);
    return ((long) x) / 2 + I(x-(long)x);
}

int main(void) {
    //first we have to find the left point of intersection with the circle. the right point is just (1/2,1/2)
    //this can be done using binsrch.
    double l = 0;
    double ly = 0;
    double r = 0.5;
    double ry = 0.5;
    for (int i = 0; i<64; i++) {
        double mid = (l+r)/2.0f;
        double midy = blanc(mid);
        if (dist(mid, midy) == 1) {
            r = mid;
            ry = midy;
        } else {
            l = mid;
            ly = midy;
        }
    }
    r = 0.5; ry = 0.5;
    //now we just have to compute the integral from l to r and subtract the part below the circle
    //i just got the recurrence to compute the integral from wikipedia because i was too lazy to do the math.
    double A1 =  I(r) - I(l); //area under curve
    double angle = M_PI - atan2(0.5-ly,0.25-l);
    double A2 = 0.5*(0.25-l)*(ly+0.5) + 0.25*0.5; //area under circle (2 trapezoids with center)
    A2 -= angle/32.0; //remove circle sector from area under circle
    printf("%.8lf\n", A1 - A2);
    return 0;
}