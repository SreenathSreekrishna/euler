//https://projecteuler.net/problem=71
//Ordered Fractions

#include <stdio.h>

int compare(int a1, int b1, int a2, int b2) {
    //returns if a1/b1>a2/b2
    return a1*b2 > a2*b1;
}

int main(void) {
    int max[2];
    max[0] = 1;
    max[1] = 100;
    for (int d = 1; d<=1000000; d++) {
        if (d % 7 ==0 ) {
            continue;
        }
        int n = ((float) d * 3) / 7;
        if (compare(n,d,max[0],max[1])) {
            max[0] = n;
            max[1] = d;
        }
    }
    printf("%d\n",max[0]);
}