//https://projecteuler.net/problem=14
//Longest Collatz sequence

#include <stdio.h>

int collatz(long n) {
    int cnt = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        }
        else {
            n = 3*n+1;
        }
        cnt += 1;
    }
    return cnt;
}

int main(void) {
    int n = 1000000;
    int max = -1;
    long maxnum = 0;
    for (long i = 1; i<n; i++) {
        int c = collatz(i);
        if (c > max) {
            max = c;
            maxnum = i;
        }
    }
    printf("%li\n", maxnum);
    return 0;
}