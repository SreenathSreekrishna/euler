//https://projecteuler.net/problem=246
//Tangents to an Ellipse

#include <stdio.h>
#include <math.h>

int main(void) {
    //translate the figure so that M is at O. Then G is at (10000,0)
    //our ellipse is the locus of points E such that EG+EM=15000
    //Let E(x,y); then sqrt((x-10000)^2 + y^2) + sqrt(x^2+y^2) = 15000
    //using this we can find that a=7500, b=2500sqrt(5)
    //translating the ellipse to centre at the origin, we can get the equation of the ellipse
    //thus the equation of the ellipse is x^2/9 + y^2/5 = 2500^2
    //by solving the tangents of the ellipse and equating the slopes using the tangent 
    //difference formula with the tangent of 45 (1), i obtain an equation for the bounding
    //region of the lattice points. this curve is given by the equation below
    //x^2 + y^2 - 14*2500^2 = 5000sqrt(5x^2 + 9(y^2 - 5*2500^2))
    //by graphing this on a graphing calculator, i find that x is between -16000 and 16000
    //and y is between -20000 and 20000. the equation is also symmetric so i only need to check
    //the pos pos quadrant and multiply by 4.
    int ans = -2; //-2 to offset for the (+-7500,0) points which are marked as inside even though they are on the ellipse
    for (int x = 0; x<16000; x++) {
        for (int y = 0; y<20000; y++) {
            double LHS = (double) x * x + (double) y * y - 87500000;
            double RHS = 5000.0*sqrt(5.0*(double)x*x + 9.0*((double)y*y-31250000));
            if (LHS < RHS) {
                if (x && y) ans += 4;
                else ans += 2;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}