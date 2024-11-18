//https://projecteuler.net/problem=80
//Square Root Digital Expansion

#include <stdio.h>
#include <math.h>
#include <string.h>
#define int_len 16
#define UINTMAX 4294967296

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

bigInt subtract(bigInt a, bigInt b) {
    bigInt result;
    bigInt_zero(&result);
    long long borrow = 0;
    for (int i = 0; i < int_len; i++) {
        result.values[i] = 0;
    }
    for (int i = 0; i < int_len; i++) {
        long long sub = (long long)a.values[i] - b.values[i] - borrow;
        if ((long long)sub < 0) {
            sub += UINTMAX;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.values[i] = sub % UINTMAX;
    }

    return result;
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

bigInt negate(bigInt x) {
    bigInt ret;
    for (int i = 0; i<int_len; i++) {
        ret.values[i] = -x.values[i];
    }
    return ret;
}

void printInt(bigInt x) {
    for (int i = 0; i<int_len; i++) {
        printf("%d ", x.values[i]);
    }
    printf("\n");
}

int sqrtsum(int n) {
    bigInt v, r;
    bigInt_zero(&v);
    bigInt_zero(&r);
    int q = sqrt(n);
    v.values[0] = 100*(n-q*q);
    r.values[0] = 2*q;

    bigInt ten;
    bigInt_zero(&ten);
    ten.values[0] = 10;

    int sum = 0;

    for (int digit = 0; digit<100; digit++) {
        sum += q;
        bigInt qbig;
        bigInt_zero(&qbig);
        for (q = 1; q<=10; q++) {
            qbig.values[0] = q;
            if (comp(multiply(qbig, add(multiply(r,ten), qbig)),v)) {
                break;
            }
        }
        q--;
        qbig.values[0]--;
        v = subtract(v, multiply(qbig,add(multiply(r,ten), qbig)));
        v = multiply(multiply(v,ten),ten);
        r = add(add(multiply(r,ten),qbig),qbig);
    }
    return sum;
}

int isSquare(int n) {
    int s = sqrt(n);
    return (s*s == n);
}

int main(void) {
    int total = 0;
    for (int i = 2; i<100; i++) {
        if (!isSquare(i)) {
            total += sqrtsum(i);
        }
    }
    printf("%d\n", total);
    return 0;
}