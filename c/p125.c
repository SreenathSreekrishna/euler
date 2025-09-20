//https://projecteuler.net/problem=125
//Palindromic Sums

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalindrome(long n) {
    int num[16] = {0};
    int numlen = 0;
    while (n>0) {
        num[numlen++] =  n % 10;
        n/=10;
    }
    for (int i = 0; i<=numlen/2; i++) {
        if (num[i] != num[numlen-i-1]) return 0;
    }
    return 1;
}

int main(void) {
    long s = 0;
    short *arr = malloc(sizeof(short) * 100000000);
    memset(arr,0,100000000);
    for (int a = 1; a<10000; a++) {
        for (int b = 0; b<a-1; b++) {
            long n = ((long) a*(a+1)*(2*a+1) - (long) b*(b+1)*(2*b+1))/6;
            if (n>100000000) continue;
            if (isPalindrome(n) && !arr[n]) {
                arr[n] = 1;
                s += n;
            }
        }
    }
    printf("%li\n", s);
    free(arr);
    return 0;
}