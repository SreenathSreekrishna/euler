//https://projecteuler.net/problem=177
//Integer Angled Quadrilaterals

#include <stdio.h>
#include <math.h>
#define DEG2RAD(x) (((double) x)*M_PI/180.0)
#define RAD2DEG(x) (((double) x)*180.0/M_PI)

int compQuad(int q1[], int q2[]) {
    for (int i = 0; i<4; i++) {
        if (q1[i] < q2[i]) return -1;
        if (q1[i] > q2[i]) return 1;
    }
    return 0;
}

int removeDuplicates(int a, int b, int c, int d, int v) {
    //remove all symmetries of a,b,c,d to ensure only distinct quads remain
    //the quadrilateral can be defined by a, b, c and d.
    //angles in order -> a, d, 180-v-d, v-c, c, b, 180-v-b, v-a
    //the symmetries are listed below.
    //a,b,c,d
    //180-v-d, v-a, 180-v-b, v-c
    //c,d,a,b
    //180-v-b, v-c, 180-v-d, v-a
    //and their reflections (for eg a,b,c,d -> b,a,d,c)
    //to enumerate only distinct ones, we return 0 when the given quad is not the lexographically minimal one
    //among its transformations and 1 if it is. thus, we only add distinct quads to the total.
    int symmetries[7][4] = {
        {b,a,d,c},
        {180-v-d,v-a,180-v-b,v-c},
        {v-a,180-v-d,v-c,180-v-b},
        {c,d,a,b},
        {d,c,b,a},
        {180-v-b,v-c,180-v-d,v-a},
        {v-c,180-v-b,v-a,180-v-d}
    };

    int original[4] = {a,b,c,d};

    int num = 0;
    for (int i = 0; i<7; i++) if (compQuad(symmetries[i], original) > 0) return 0;
    return 1;
}

double si[180];
double co[180];

int valid(int a, int b, int c, int d) {
    if (a+b >= 180 || c+d >= 180) return 0; //Angle sum >180
    if (a+d >= 180 || b+c >= 180) return 0; //Convex quad 
    double num = si[a]*si[b]*(si[c]*co[d] + si[d]*co[c]) + si[c]*si[d]*(si[a]*co[b] + si[b]*co[a]);
    double den = co[a]*si[b]*(si[c]*co[d] + si[d]*co[c]) - si[c]*co[d]*(si[a]*co[b] + si[b]*co[a]);
    double ang = RAD2DEG(atan2(num,den));
    int v = round(ang);
    if (fabs(ang - v) > 1e-9) return 0;
    if (!removeDuplicates(a,b,c,d,v)) return 0;
    return 1;
}

int main(void){
    //i solve this problem with bruteforce enumeration of integer angled quads, check if its valid using trig
    //and then just remove duplicates using lexographic minimality. i also store sin and cos of integer angles
    //in a lookup table for fast calculations (improves program runtime by ~50%).
    //i loop over integer values of angles ABD (a), ADB (b), CDB (c) and CBD (d).
    //Using some trig, i calculate v = AOD (O is intersection of AC,BD). notice that by the angle sum property,
    //if AOD is an integer, all the required angles are also integers. Also notice that the four angles
    //i am looping over (a,b,c,d) are enough to determine the unique quadrilateral upto similarity.
    //thus, all that is left is to remove convex quads and duplicates caused by symmetries of the same quad.

    int count = 0;
    for (int i = 0; i<180; i++) {
        si[i] = sin(DEG2RAD(i));
        co[i] = cos(DEG2RAD(i));
    }

    for (int a = 1; a <= 179; a++)
    for (int d = 1; a+d <= 179; d++)
    for (int b = 1; a+b <= 179; b++)
    for (int c = 1; c+d <= 179 && b+c <= 179; c++)
        count += valid(a,b,c,d);

    printf("%d\n", count);
    return 0;
}