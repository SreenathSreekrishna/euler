//https://projecteuler.net/problem=119
//Digit Power Sum

#include <stdio.h>

int digitSum(long long n) {
    int s = 0;
    while (n>0) {
        s += n%10;
        n /= 10;
    }
    return s;
}

int main(void) {
    long max = 1000000000000000;
    int k = 0;
    long m = -1;
    for (int j = 2; j<10000; j++) {
        for (long n = j*j; n<max; n*=(long)j) {
            if (j == digitSum(n)) {
                if (n>m) m = n;
                k++;
            }
        }
    }
    //i ran the program once and k comes out to exactly 30. that's why i just take the maximum instead of sorting
    printf("%li\n", m);
    return 0;
}