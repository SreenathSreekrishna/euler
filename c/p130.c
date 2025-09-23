//https://projecteuler.net/problem=130
//Composites with Prime Repunit Property

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    for (int i = 2; i<sqrt(n)+1; i++) if (n % i == 0) return 0;
    return 1;
}

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

int phi(int n) {
    //least k such that 10^k = 1 mod n
    int p = n;
    int t = n;
    while (t>1) {
        for (int i = 2; i<=t; i++) {
            if (t % i == 0) {
                t /= i;
                p /= i;
                p *= (i-1);
                while (t%i == 0) {
                    t /= i;
                }
            }
        }
    }
    return p;
}

int main(void) {
    int s = 0;
    int cnt = 0;
    int i = 2;
    while (cnt < 25) {
        i++;
        if (gcd(i,10) > 1) continue;
        int m = i;
        if (m%3 == 0) m*=9;
        if (isPrime(m) || power(10,gcd(phi(m),i-1),m) != 1) continue;
        cnt++;
        s += i;
    }
    printf("%d\n", s);
    return 0;
}