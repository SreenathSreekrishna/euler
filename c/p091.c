//https://projecteuler.net/problem=91
//Right Triangles with Integer Coordinates

#include <stdio.h>

int isTriangle(int x1, int y1, int x2, int y2) {
    int a2 = x1*x1 + y1*y1;
    int b2 = x2*x2 + y2*y2;
    int c2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    return (a2 + b2 == c2 || b2 + c2 == a2 || c2 + a2 == b2);
}

int main(void) {
    int n = 0;
    for (int x1 = 0; x1<=50; x1++) {
        for (int y1 = 0; y1<=50; y1++) {
            for (int x2 = 0; x2<=50; x2++) {
                for (int y2 = 0; y2<=50; y2++) {
                    if (isTriangle(x1,y1,x2,y2) && x1*y2 < x2*y1) {
                        n++;
                    }
                }
            }
        }
    }
    printf("%d\n", n);

    return 0;
}