//https://projecteuler.net/problem=104
//Pandigital Fibonacci Ends

#include <stdio.h>

long m = (long) 10*10*10*10*10*10*10*10*10;
unsigned long long max = (unsigned long long) 10*10*10*10*10*10*10*10*10*10*10*10*10*10*10*10*10*10;

int checkPandigital(int n) {
    int digits[10] = {0};
    while (n) {
        digits[n%10]++;
        n /= 10;
    }
    for (int i = 1; i<10; i++) {
        if (digits[i] != 1) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    long a = 0;
    long b = 1;
    unsigned long long siga = 0;
    unsigned long long sigb = 1;
    int n = 0;
    while (1) {
        b = a+b;
        a = b-a;
        a %= m;
        b %= m;
        sigb = siga + sigb;
        siga = sigb - siga;
        if (siga > max && sigb > max) {
            siga /= 10;
            sigb /= 10;
        }
        if (checkPandigital(siga / m) && checkPandigital(a)) {
            printf("%d\n", n+1);
            return 0;
        }
        n++;
        if (a == 0 && b == 1) {
            break;
        }
    }
}