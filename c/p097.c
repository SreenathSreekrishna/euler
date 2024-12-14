//https://projecteuler.net/problem=97
//Large Non-Mersenne Prime

#include <stdio.h>
#include <string.h>
#define int_len 16
#define UINTMAX 100000

typedef struct bigInt {
    unsigned int values[int_len];
} bigInt;

void bigInt_zero(bigInt *a) {
    memset(a->values, 0, sizeof(a->values));
}

bigInt add(bigInt a, bigInt b) {
    bigInt s;
    bigInt_zero(&s);

    long long carry = 0;
    for (int i = 0; i < int_len; i++) {
        long long v = (long long)a.values[i] + b.values[i] + carry;
        s.values[i] = v % UINTMAX;
        carry = v / UINTMAX;
    }
    return s;
}

bigInt multiply(bigInt a, bigInt b) {
    bigInt result;
    bigInt_zero(&result);

    for (int i = 0; i < int_len; i++) {
        long long carry = 0;  

        for (int j = 0; j < int_len - i; j++) {
            long long product = (long long)a.values[i] * b.values[j];
            long long sum = (long long)result.values[i + j] + product + carry;
            result.values[i + j] = sum % UINTMAX;
            carry = sum / UINTMAX;
        }
        if (i + 1 < int_len) {
            result.values[i + 1] += carry;
        }
    }

    return result;
}

int main(void) {
    //i will use the russian peasant method for this problem
    bigInt m,v,x;
    bigInt_zero(&m);
    bigInt_zero(&v);
    bigInt_zero(&x);
    m.values[1] = 1;
    v.values[0] = 1;
    x.values[0] = 2;
    int p = 7830457;
    while (p > 0) {
        if (p % 2) {
            v = multiply(v,x);
        }
        x = multiply(x,x);
        for (int i = 4; i<10; i++) {
            x.values[i] = 0;
            v.values[i] = 0;
        }
        p /= 2;
    }
    bigInt n;
    bigInt_zero(&n);
    n.values[0] = 28433;
    v = multiply(n,v);
    printf("%u%u\n",v.values[1],v.values[0]+1);
    return 0;
}