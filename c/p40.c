//https://projecteuler.net/problem=40
//Champernowne's Constant

#include <stdio.h>
#include <math.h>

int main(void) {
    int numDigitsTotal = 9+90*2+900*3+9000*4+90000*5+900000*6+7;
    char d[numDigitsTotal];
    int pos = 0;
    for (int i = 1; i<=1000000; i++) {
        int numDigits = log10(i) + 1;
        int pow = 10;
        for (int j = (numDigits-1); j>=0; j--) {
            char c = (i % pow) / (pow / 10);
            d[pos+j] = c;
            pow *= 10;
        }
        pos += numDigits;
    }
    printf("%d\n", d[0]*d[9]*d[99]*d[999]*d[9999]*d[99999]*d[999999]);
}