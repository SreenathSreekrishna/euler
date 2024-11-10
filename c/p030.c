//https://projecteuler.net/problem=30
//Digit Fifth Powers

#include <stdio.h>

int main(void) {
    int i = 10;
    int s = 0;
    while (i < 10000000) {
        int m = i / 1000000;
        int ht = (i % 1000000) / 100000;
        int tt = (i % 100000) / 10000;
        int th = (i % 10000) / 1000;
        int h = (i % 1000) / 100;
        int t = (i % 100) / 10;
        int o = i % 10;
        if (m*m*m*m*m + ht*ht*ht*ht*ht + tt*tt*tt*tt*tt + th*th*th*th*th + h*h*h*h*h + t*t*t*t*t + o*o*o*o*o == i) {
            s += i;
        }
        i++;
    }
    printf("%d\n", s);
    return 0;
}