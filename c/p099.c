//https://projecteuler.net/problem=99
//Largest Exponential

#include <stdio.h>
#include <math.h>

int cmp(int a, int p1, int b, int p2) {
    //returns if a^p1 > b^p2
    double v1 = (double) p1*(double) log(a);
    double v2 = (double) p2 * (double) log(b);
    return  v1> v2;
}

int main(void) {
    FILE *f = fopen("../files/p099_base_exp.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    int max = 2;
    int maxp = 2;
    int maxi;
    for (int i = 0; i<1000; i++) {
        int n,p;
        fscanf(f,"%d,%d\n",&n,&p);
        if (cmp(n,p,max,maxp)) {
            max = n;
            maxp = p;
            maxi = i;
        }
    }
    printf("%d\n", maxi+1);
    return 0;
}