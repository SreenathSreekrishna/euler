//https://projecteuler.net/problem=51
//Prime Digit Replacements

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n <= 3) {
        return 1;
    }
    for (int i = 2; i<sqrt((float) n)+1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int numDigits(int n) {
    int k = 1;
    while (n >= 10) {
        k ++;
        n = n / 10;
    }
    return k;
}

int digitsToNum(int digits[16]) {
    int p = 1;
    int n = 0;
    int i = 0;
    while (digits[i] >=0 && digits[i] < 10) {
        n += digits[i]*p;
        p*=10;
        i++;
    }
    return n;
}

int main(void) {
    int n = 56003;
    while (1) {

    int digitCount[10] = {0};
    int digits[16];
    for (int i  = 0; i<16; i++) {
        digits[i] = -1;
    }
    int n_ = n;
    int i = 0;
    while (n_ != 0) {
        digits[i] = n_ % 10;
        n_ = n_ / 10;
        digitCount[digits[i]]++;
        i++;
    }

    int m = -1;
    int m_i = -1;

    for (int k = 0; k<10; k++) {
        if (digitCount[k] > m) {
            m = digitCount[k];
            m_i = k;
        }
    }

    int digits1[16];

    int count = 0;

    for (int d = 0; d<10; d++) {
        for (int k = 0; k<16; k++) {
            if (digits[k] == m_i) {
                digits1[k] = d;
            }
            else {
                digits1[k] = digits[k];
            }
        }
        int p = digitsToNum(digits1);
        if (digits1[i-1] == 0 || !isPrime(p)) {
            count++;
        }
        if (count > 2) {
           break;
        }
    }

    if (count == 2) {
        printf("%d\n",n);
        return 0;
    }

    n++;
    }
}