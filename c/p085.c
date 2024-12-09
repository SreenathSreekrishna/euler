//https://projecteuler.net/problem=85
//Counting Rectangles

#include <stdio.h>

int abs(int x) {
    if (x < 0) return -x;
    return x;
}

int main(void) {
    //number of rectangles in AxB grid is (A+1)(B+1)AB/4

    int min_x, min_y;
    int min = 2000000;

    for (int x = 1; x<=2000000; x++) {
        for (int y = 1, b = 2000000/x; y<=b; y++) {
            int num = (x+1)*(y+1)*x*y / 4;
            int diff = abs(num - 2000000);
            if (diff < min) {
                min = diff;
                min_x = x;
                min_y = y;
            }
        }
    }
    printf("%d\n",min_x*min_y);

    return 0;
}