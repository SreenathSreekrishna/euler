//https://projecteuler.net/problem=138
//Special Isosceles Triangles

#include <stdio.h>

int main(void) {
    //h = b+-1
    //4h^2 + b^2 = 4L^2
    //25b^2 +-10b + 5 = 20L^2
    //(5b+-1)^2 - 20L^2 = 4
    //k^2 - 20L^2 = 4
    //m^2 - 5L^2 = 1
    long m = 2;
    long L = 1;
    long sum = 0;
    for (int i = 0; i<12; i++) {
        long tmp = m;
        m = 9*m + 20*L;
        L = 4*tmp + 9*L;
        sum += L;
    }
    printf("%ld\n" ,sum);
    return 0;
}