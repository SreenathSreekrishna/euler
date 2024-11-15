//https://projecteuler.net/problem=66
//Diophantine Equation

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define UINTMAX 4294967296
#define int_len 4

typedef struct bigInt {
    unsigned int values[int_len];
} bigInt;

bigInt P;
bigInt Q;

int gcd(int a, int b) {
    if (a == b) {
        return a;
    }
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    if (b>a) {
        return gcd(a,b % a);
    }
    if (a>b) {
        return gcd(b,a % b);
    }
    return 1;
}

int *cotdFrac(int n) {
    //reused code from p064 ;)
    //gives the coefficients in the continued fraction of sqrt(n)
    int prevStates[10000][4];
    int *a = malloc(sizeof(int)*10000);
    for (int i = 0; i<10000; i++) {
        a[i] = 0;
    }
    int p = 1;
    int q = 0;
    int r = 1;
    for (int i = 0; i<10000; i++) {
        a[i] = (int) (((float) sqrt(n)*p + q) / r);
        int p1 = r*p;
        int q1 = r*r*a[i]-r*q;
        int r1 = p*p*n-q*q+2*a[i]*q*r-a[i]*a[i]*r*r;
        int g = gcd(gcd(p1,q1),r1);
        p = p1 / g;
        q = q1 / g;
        r = r1 / g;
        int l[4] = {a[i],p,q,r};
        for (int j = 0; j<i; j++) {
            int fail = 1;
            for (int k = 0; k<4; k++) {
                if (prevStates[j][k] != l[k]) {
                    fail = 0;
                    break;
                }
            }
            if (fail) {
                return a;
            }
        }
        for (int j = 0; j<4; j++) {
            prevStates[i][j] = l[j];
        }
    }
    return a;
}

void bigInt_zero(bigInt *a) {
    memset(a->values, 0, sizeof(a->values));
}

bigInt add(bigInt a, bigInt b) {
    bigInt s;
    bigInt_zero(&s);

    unsigned long long carry = 0;
    for (int i = 0; i < int_len; i++) {
        unsigned long long v = (unsigned long long)a.values[i] + b.values[i] + carry;
        s.values[i] = v % UINTMAX;
        carry = v / UINTMAX;
    }
    return s;
}

bigInt multiply(bigInt a, bigInt b) {
    bigInt result;
    bigInt_zero(&result);

    for (int i = 0; i < int_len; i++) {
        unsigned long long carry = 0;  

        for (int j = 0; j < int_len - i; j++) {
            unsigned long long product = (unsigned long long)a.values[i] * b.values[j];
            unsigned long long sum = (unsigned long long)result.values[i + j] + product + carry;
            result.values[i + j] = sum % UINTMAX;
            carry = sum / UINTMAX;
        }
        if (i + 1 < int_len) {
            result.values[i + 1] += carry;
        }
    }

    return result;
}

int comp(bigInt a, bigInt b) {
    //returns if a>b
    for (int i = int_len-1; i>=0; i--) {
        if (a.values[i] > b.values[i]) {
            return 1;
        }
        if (b.values[i] > a.values[i]) {
            return 0;
        }
    }
    return 0;
}

void cotdFracNum(int *a, int n) {
    //returns the numerator of the approximation upto n terms of the continued fraction
    bigInt p;
    bigInt q;
    bigInt_zero(&p);
    bigInt_zero(&q);
    p.values[0] = 1;
    for (int i = n-1; i>=0; i--) {
        bigInt tmp = p;
        bigInt ai;
        bigInt_zero(&ai);
        ai.values[0] = a[i];
        p = add(multiply(p,ai),q);
        q = tmp;
    }
    P = p;
    Q = q;
}

int main(void) {
    bigInt max;
    for (int i = 0; i<int_len; i++) {
        max.values[i] = 0;
    }
    int max_i = -1;
    for (int i = 1; i<=1000; i++) {
        int *expansion = cotdFrac(i);
        int n = 0;
        while (expansion[n]) n++;
        cotdFracNum(expansion,n-2);
        bigInt x;
        if (n % 2 == 0) {
            x = P;
        }
        else {
            bigInt I;
            bigInt_zero(&I);
            I.values[0] = i;
            x = add(multiply(P,P),multiply(multiply(Q,Q),I));
        }
        if (comp(x,max)) {
            max_i = i;
            max = x;
        }
        free(expansion);
    }
    printf("%d\n", max_i);
    return 0;
}