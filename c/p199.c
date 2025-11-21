//https://projecteuler.net/problem=199
//Iterative Circle Packing

#include <stdio.h>
#include <math.h>
#define N 10
#define MEMBOUND 100000

typedef struct hole {
    double b1;
    double b2;
    double b3;
} hole;

int main(void) {
    //notice that upon adding a new circle to the diagram, exactly 3 new holes are created and one is removed.
    //we also see that each hole can be uniquely defined by just the curvatures of the three circles enclosing
    //it. (we make the curvature of the outer circle negative as it is externally tangent to all the circles
    //whereas all the other circles are internal). now, i just use decartes' theorem of kissing circles to
    //solve for the curvature of the largest circle that fits in a hole, adding the areas along the way.
    //as i am only concerned with the ratio with the original circle, i remove the factor of pi for all the
    //circles that i add.
    hole holes[MEMBOUND];
    int numHoles = 4;
    double b = 1.0F/(2*sqrt(3) - 3); //curvature of 3 initial circles
    double area = 63.0F-36*sqrt(3); //area of 3 initial circles (i am removing pi factor because it cancels out)
    holes[0] = (hole) {b,b,b};
    holes[1] = holes[2] = holes[3] = (hole) {b,b,-1};
    for (int _ = 0; _<N; _++) {
        hole newHoles[MEMBOUND];
        int numNewHoles = 0;
        for (int i = 0; i<numHoles; i++) {
            hole h = holes[i];
            double newb = h.b1+h.b2+h.b3+2.0F*sqrt(h.b1*h.b2+h.b2*h.b3+h.b3*h.b1);
            area += 1.0F/(newb*newb);
            if (numNewHoles >= MEMBOUND-3) continue;
            newHoles[numNewHoles++] = (hole) {newb, h.b1, h.b2};
            newHoles[numNewHoles++] = (hole) {newb, h.b2, h.b3};
            newHoles[numNewHoles++] = (hole) {newb, h.b3, h.b1};
        }
        for (int i = 0; i<numNewHoles; i++) holes[i] = newHoles[i];
        numHoles = numNewHoles;
    }
    printf("%.8lf\n", 1-area);
    return 0;
}