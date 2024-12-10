//https://projecteuler.net/problem=89
//Roman Numerals

#include <stdio.h>
#include <string.h>

int romanLength;

int getValue(char numeral) {
    if (numeral == 'I') return 1;
    if (numeral == 'V') return 5;
    if (numeral == 'X') return 10;
    if (numeral == 'L') return 50;
    if (numeral == 'C') return 100;
    if (numeral == 'D') return 500;
    if (numeral == 'M') return 1000;
    return 0;
}

int convertRoman(char numerals[32]) {
    int values[32] = {0};
    int s = 0;
    int n = 0;
    for (int i = 0; numerals[i]; i++,n++) {
        values[i] = getValue(numerals[i]);
        s += values[i];
    }
    romanLength = n;
    for (int i = 1; i<n; i++) {
        if (values[i-1] < values[i]) {
            s -= 2*values[i-1];
        }
    }
    return s;
}

int numeralDigits(int n) {
    //least number of roman numerals needed to express n
    int values[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    int t = 0;
    for (int i = 0; n; i++) {
        while (n >= values[i]) {
            t += (i%2)+1;
            n -= values[i];
        }
    }
    return t;
}

int main(void) {
    FILE *f = fopen("../files/0089_roman.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    int v = 0;

    for (int i = 0; i<1000; i++) {
        char str[32] = {0};
        int n = fscanf(f,"%s\n",&str[0]);
        int value = convertRoman(str);
        v += romanLength - numeralDigits(value);
    }

    printf("%d\n", v);

    return 0;
}