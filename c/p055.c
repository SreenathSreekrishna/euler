//https://projecteuler.net/problem=55
//Lychrel Numbers

#include <stdio.h>
#include <stdlib.h>

int isPalindrome(int *digits) {
    int z;
    for (int i = 0; i<32; i++) {
        if (digits[i]) {
            z = i;
        }
    }
    for (int i = 0; i<=z/2; i++) {
        if (digits[i] != digits[z-i]) {
            return 0;
        }
    }
    return 1;
}

int *reverse(int *digits) {
    int z;
    int *rev = malloc(sizeof(int) * 32);
    for (int i = 0; i<32; i++) {
        if (digits[i]) {
            z = i;
        }
        rev[i] = 0;
    }

    for (int i = 0; i<=z; i++) {
        rev[i] = digits[z-i];
    }
    return rev;
}

int *add(int *d1, int *d2) {
    int *s = malloc(sizeof(int) * 32);
    for (int i = 0; i<32; i++) {
        s[i] = 0;
    }
    for (int i = 0; i<32; i++) {
        int m = s[i] + d1[i] + d2[i];
        s[i] = m % 10;
        s[i+1] += ((m - (m % 10)) / 10);
    }
    return s;
}

int *intDigits(int n) {
    int *digits = malloc(sizeof(int) * 32);
    for (int i = 0; i<32; i++) {
        digits[i] = n % 10;
        n /= 10;
    }
    return digits;
}

int main(void) {
    int c = 0;
    for (int N = 0; N<10000; N++) {
        int *n = intDigits(N);
        int i;
        for (i = 0; i<50; i++) {
            int *m = reverse(n);
            int *s = add(m,n);
            free(n);
            free(m);
            n = s;
            if (isPalindrome(n)) {
                break;
            }
        }
        if (i == 50) {
            c++;
        }
        free(n);
    }
    
    printf("%d\n", c);
    return 0;
}