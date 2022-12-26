//https://projecteuler.net/problem=9
//Special Pythagorean triplet

#include <stdio.h>

int main(void) {
    //https://en.wikipedia.org/wiki/Formulas_for_generating_Pythagorean_triples#Dickson's_method
    //this is the method i am using
    int n = 1000;
    int r = 2;
    while (1) {
        int mult = r*r/2;
        for (int s = 1; s <= r; s++) {
            if (mult % s == 0) {
                int t = mult / s;
                int a = r+s;
                int b = r+t;
                int c = r+s+t;
                if (a+b+c == n) {
                    printf("%d\n", a*b*c);
                    return 0;
                }
            }
        }
        r+=2;
    }
}