//https://projecteuler.net/problem=36
//Double-base Palindromes

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int palindrome(int n, int b) {
    int len = (int) (log(n)/log(b)) + 1;
    int *num = malloc(sizeof(int) * len);
    for (int i = 0; i<len; i++) {
        num[i] = (n / (int) pow(b, i)) % b;
    }
    for (int i = 0; i<len / 2; i++) {
        if (num[i] != num[len-i-1]) {
            free(num);
            return 0;
        }
    }
    free(num);
    return 0;
}

int main() {
    int s = 0;
    for (int i = 1; i<1000000; i++) {
        if (palindrome(i, 2) && palindrome(i, 10)) {
            s+=i;
        }
    }
    printf("%d\n", s);
    return 0;
}