//https://projecteuler.net/problem=32
//Pandigital Products

#include <stdio.h>
#include <math.h>

int pandigital(int a, int b) {
    int c = a * b;
    int aDigits = log10(a) + 1;
    int bDigits = log10(b) + 1;
    int cDigits = log10(c) + 1;
    if (aDigits + bDigits + cDigits != 9) {
        return 0;
    }
    int digits[10] = {0};
    for (int power = 1; power<=aDigits; power++) {
        int val = pow(10, power);
        int digit = (a % val) * 10 / val;
        digits[digit]++;
    }
    for (int power = 1; power<=bDigits; power++) {
        int val = pow(10, power);
        int digit = (b % val) * 10 / val;
        digits[digit]++;
    }
    for (int power = 1; power<=cDigits; power++) {
        int val = pow(10, power);
        int digit = (c % val) * 10 / val;
        digits[digit]++;
    }
    if (digits[0] != 0) {
        return 0;
    }
    for (int i = 1; i<10; i++) {
        if (digits[i] != 1) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int solutions[128] = {-1};
    int idx = 0;
    int s = 0;
    for (int i = 1; i<2048; i++) {
        for (int j = 1; j<2048; j++) {
            if (pandigital(i,j)) {
                int p = i*j;
                int found = 0;
                for (int k = 0; k<128; k++) {
                    if (solutions[k] == p) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    solutions[idx] = p;
                    s += p;
                    idx++;
                }
            }
        }
    }
    printf("%d\n", s);
}