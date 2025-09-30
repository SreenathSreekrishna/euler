//https://projecteuler.net/problem=142
//Perfect Square Collection

#include <stdio.h>
#include <math.h>

int isSquare(long n) {
    if (n<0) return 0;
    long s = sqrt(n);
    return (s*s == n) * s;
}

int main(void) {
    //a^2 + b^2 = c^2 + d^2 = 2x
    //a^2 - b^2 = e^2 + f^2 = 2y
    //c^2 - d^2 = e^2 - f^2 = 2z
    //a^2 = c^2 + f^2 = d^2 + e^2
    //c^2 = b^2 + e^2
    //d^2 = b^2 + f^2
    int a = 1;
    while (1) {
        for (int c = 1; c<a; c++) {
            for (int d = 1; d<c; d++) {
                int b = isSquare(c*c-a*a+d*d);
                int e = isSquare(a*a-d*d);
                int f = isSquare(a*a-c*c);
                if (!b || !e || !f) continue;
                if ((a+b)%2 || (c+d)%2) continue;
                int x = (a*a+b*b)/2;
                int y = (a*a-b*b)/2;
                int z = (c*c-d*d)/2;
                printf("%d\n",x+y+z);
                return 0;
            }
        }
        a++;
    }
    return 0;
}