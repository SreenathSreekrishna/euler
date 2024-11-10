//https://projecteuler.net/problem=49
//Prime Permutations

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

int isPerm(int a, int b) {
    //checks if digits of b is a permutation of digits of a
    //a,b are four digit numbers
    int x1 = a/1000;
    int x2 = ((int) (a/100)) % 10;
    int x3 = ((int) (a/10)) % 10;
    int x4 = a % 10;

    int y1 = b/1000;
    int y2 = ((int) (b/100)) % 10;
    int y3 = ((int) (b/10)) % 10;
    int y4 = b % 10;

    return
    ((x1 == y1 && x2 == y2 && x3 == y4 && x4 == y3) ||
    (x1 == y1 && x2 == y2 && x3 == y4 && x4 == y3) ||
    (x1 == y1 && x2 == y3 && x3 == y2 && x4 == y4) ||
    (x1 == y1 && x2 == y3 && x3 == y4 && x4 == y2) ||
    (x1 == y1 && x2 == y4 && x3 == y2 && x4 == y3) ||
    (x1 == y1 && x2 == y4 && x3 == y3 && x4 == y2) ||
    (x1 == y2 && x2 == y1 && x3 == y4 && x4 == y3) ||
    (x1 == y2 && x2 == y1 && x3 == y4 && x4 == y3) ||
    (x1 == y2 && x2 == y3 && x3 == y1 && x4 == y4) ||
    (x1 == y2 && x2 == y3 && x3 == y4 && x4 == y1) ||
    (x1 == y2 && x2 == y4 && x3 == y1 && x4 == y3) ||
    (x1 == y2 && x2 == y4 && x3 == y3 && x4 == y1) ||
    (x1 == y3 && x2 == y2 && x3 == y4 && x4 == y1) ||
    (x1 == y3 && x2 == y2 && x3 == y4 && x4 == y1) ||
    (x1 == y3 && x2 == y1 && x3 == y2 && x4 == y4) ||
    (x1 == y3 && x2 == y1 && x3 == y4 && x4 == y2) ||
    (x1 == y3 && x2 == y4 && x3 == y2 && x4 == y1) ||
    (x1 == y3 && x2 == y4 && x3 == y1 && x4 == y2) ||
    (x1 == y4 && x2 == y2 && x3 == y3 && x4 == y1) ||
    (x1 == y4 && x2 == y2 && x3 == y3 && x4 == y1) ||
    (x1 == y4 && x2 == y1 && x3 == y2 && x4 == y3) ||
    (x1 == y4 && x2 == y1 && x3 == y3 && x4 == y2) ||
    (x1 == y4 && x2 == y3 && x3 == y2 && x4 == y1) ||
    (x1 == y4 && x2 == y3 && x3 == y1 && x4 == y2));
}

int main(void) {
    for (int i = 1001; i<10000; i+=2) {
        for (int k = i+2; k<10000; k+=2) {
            int j = (i+k)/2;
            if (!(isPrime(i) && isPrime(j) && isPrime(k)) || i == 1487) {
                continue;
            }
            if (isPerm(i,j) && isPerm(j,k)) {
                printf("%d%d%d\n",i,j,k);
            }
        }
    }
    return 0;
}