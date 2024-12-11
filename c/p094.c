//https://projecteuler.net/problem=94
//Almost Equilateral Triangles

#include <stdio.h>

int main(void) {
    //for triangle with sides n,n,n+-1 to have integral area, its height must be integral
    //(3m-1)^2 - 3h^2= 1
    //x^2 - 3h^2 = 1
    //x = 1,2,7,26 ...
    //x = 3m-1
    //n = (2x-1)/3 OR n = (2x+1)/3 => p = 2x-2 OR p = 2x+2
    //3h^2 + 1 = (3m-1)^2 OR (3m-2)^2
    //12h^2=(6m-3+-1)^2 - 4 =>3h^2=(3m-2)^2-1 OR (3m-1)^2-1

    long s = 0;

    int x_prev = 1;
    int x = 2;
    while (x<=100000000) {
        int tmp = x_prev;
        x_prev = x;
        x = 4*x - tmp;
        s += (2*x + 2*(2*(x%2)-1));
    }
    printf("%ld\n", s);

    return 0;
}