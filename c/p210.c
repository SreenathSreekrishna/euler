//https://projecteuler.net/problem=210
//Obtuse Angled Triangles

#include <stdio.h>
#include <math.h>
#define N 1000000000LL

long long sqrti(long long x) {
    //integer sqrt function that adjusts sqrtl that is sometimes a little off.
    //i found this to be much more efficient than doing a pure integer binsrch sqrt.
    if (x <= 0) return 0;
    long long r = sqrtl((long double) x);
    while (r * r > x) r--;
    return r;
}

int main(void) {
    //by drawing a diagram and seeing when each of the three angles becomes obtuse, i see that obtuse angle
    //occurs when - 
    //a) B lies in the region below line y = -x
    //b) B lies in the region above line y = r/2 - x
    //c) B lies in the interior of circle with centre (r/8, r/8) and radius r/4rt2.
    //we also have to subtract off (d), which is the case where B is collinear which we are overcounting.
    //this means we subtract off r-1, which is the overcounting.
    //These regions are also disjoint so we can simply sum the points for each case.
    //for (a) the count comes out to 2+4+6+8+10...r + (r/2)*r + 1+3+5+7+9+11+...(r-1)
    //Thus (a) -> r^2 + r/2
    //for (b) the count is 1+3+...(r/2 - 1) + (3r/4)(r/2) + 2+4+6...r/2
    //Thus (b) -> r^2/2 + r/4
    //Thus the sum of the first 2 cases after removing all overcounting (d) is r^2 + r/2 + r^2/2 + r/4 -r+1
    //   = (6r^2 - r + 4)/4
    //(c) is where it gets little more complicated. there is no set formula to compute it, as it is related
    //to the gauss circle counting problem in number theory which does not have a nice closed form.
    //thus i just check one quadrant of circle for lattice points and use symmetry.

    long A = sqrti(N*N/32);
    long C = 0;
    for (long x = 1; x<=A; x++) C += sqrti(N*N/32 - x*x - 1); //-1 to prevent boundary points
    C = 4*(A+C)+1;
    printf("%lld\n", (6*N*N - N + 4)/4 + C);
    return 0;
}