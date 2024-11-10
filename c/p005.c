//https://projecteuler.net/problem=5
//Smallest multiple

#include <stdio.h>

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n = 20;
    int result = 1;
    int i;
    for (i = 2; i <= n; i++) {
        int r = result % i;
        if (r != 0) {
            result = lcm(result, i);
        }
    }
    printf("%d\n", result);
    return 0;
}