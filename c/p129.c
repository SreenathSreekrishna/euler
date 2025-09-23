//https://projecteuler.net/problem=129
//Repunit Divisibility

#include <stdio.h>
#include <math.h>

long long power(long long b, long long e, long long m) {
    //b^e mod m
    long long res = 1;
    b %= m;
    while (e > 0) {
        if (e % 2) res = (res * b) % m;
        b = (b*b) % m;
        e /= 2;
    }
    return res;
}

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b,a%b);
}

int check(int k, int n) {
    //finds a k' < k such that 10^k' = 1 mod n
    for (int i = 2; i<sqrt(k)+1; i++) {
        if (k%i == 0 && power(10,k/i,n) == 1) {
            return check(k/i,n);
        }
    }
    return k;
}

int A(int n) {
    if (gcd(n,10) > 1) return 0;
    if (n%3 == 0) n*=9;
    //least k such that 10^k = 1 mod n
    int phi = n;
    int t = n;
    while (t>1) {
        for (int i = 2; i<=t; i++) {
            if (t % i == 0) {
                t /= i;
                phi /= i;
                phi *= (i-1);
                while (t%i == 0) {
                    t /= i;
                }
            }
        }
    }
    return check(phi,n);
}

int main(void) {
    //R(k) = (10^k - 1) / 9
    //as A(n)<=phi(n)<n, and we want A(n)>1000000, we only have to check from n=1000000 onwards
    int a = 0;
    int i = 1000000;
    while (a<1000000) {
        i++;
        a = A(i);
    }
    printf("%d\n", i);
    return 0;
}