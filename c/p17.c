//https://projecteuler.net/problem=17
//Number letter counts

#include <stdio.h>

int main(void) {
    int n = 1000;
    int letters = 0;
    int ones[10] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4};
    int tens[10] = {0, 3, 6, 6, 5, 5, 5, 7, 6, 6};
    int powers[2] = {10, 8};
    for (int i = 20; i<=n; i++) {
        int num = i;
        int onesPlace = num % 10;
        num /= 10;
        int tensPlace = num % 10;
        num /= 10;
        int hundredsPlace = num % 10;
        num /= 10;
        int thousandsPlace = num % 10;
        if (hundredsPlace) {
            letters += (ones[hundredsPlace] + powers[0]);
        }
        if (thousandsPlace) {
            letters += (ones[thousandsPlace] + powers[1]);
        }
        letters += (ones[onesPlace] + tens[tensPlace]);
    }
    printf("%d\n", letters+115);
    return 0;
}