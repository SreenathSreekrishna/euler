//https://projecteuler.net/problem=206
//Concealed Square

#include <stdio.h>
#include <math.h>

int main(void) {
    //as last digit is 0, second last must also be 0.
    //thus problem is reduced to finding the hidden square 1_2_3_4_5_6_7_8_9
    int min = sqrt(10203040506070809);
    int max = sqrt(19293949596979899);
    for (int i = min; i<=max; i++) {
        if (i%10 != 3 && i%10 != 7) continue;
        long sq = (long) i*i;
        long n = sq;
        int digits[20] = {0};
        int digitsLen = 0;
        while (n) {
            digits[digitsLen++] = n%10;
            n /= 10;
        }
        int invalid = 0;
        for (int j = 0; j<digitsLen; j+=2) {
            if (digits[j] != 9-j/2) {
                invalid = 1;
                break;
            }
        }
        if (!invalid) {
            printf("%d0\n", i);
            break;
        }
    }
    return 0;
}