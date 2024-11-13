//https://projecteuler.net/problem=63
//Powerful Digit Counts

#include <stdio.h>

int main(void) {
    int n = 1;
    for (int d = 1; d<10; d++) {
        double t = (double)10/d;
        double x = 1;
        int k = 0;
        while (x < 10) {
            x *= t;
            n++;
            k++;
        }
        n--;
    }
    printf("%d\n",n);
}