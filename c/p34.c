//https://projecteuler.net/problem=34
//Digit Factorials

#include <stdio.h>
#include <math.h>

int factorial(int n) {
    int m = 1;
    for (int i = 1; i<=n; i++) {
        m*=i;
    }
    return m;
}

int main(void) {
    int s = 0;
    for (int i = 10; i<100000; i++) {
        int numDigits = log10(i) + 1;
        int facSum = 0;
        for (int j = 1; j<=numDigits; j++) {
            int n = pow(10, j);
            facSum += factorial((i%n) * 10 / n);
        }
        if (facSum == i) {
            s += i;
        }
    }
    printf("%d\n", s);
    return 0;
}