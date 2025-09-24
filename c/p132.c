//https://projecteuler.net/problem=132
//Large Repunit Factors

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

int isPrime(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    for (int i = 2; i<sqrt(n)+1; i++) if (n % i == 0) return 0;
    return 1;
}

int main(void) {
    //To find small factors of R(10^9), notice that if p | R(10^9), 10^(10^9) = 1 mod p
    //This means 10^GCD(10^9,p-1) = 1 mod p
    //So we just have to check if nk+1 is prime for all k | 10^9. if it is, we just have to check
    //the previous condition
    long n = 1000000000;
    int a = 0;
    int s = 0;
    short used[1000000] = {0};
    for (long i = 2; i<(float)10000*sqrt(10)+1; i++) {
        if (n%i) continue;
        int  v = 0;
        for (int k = 1; v<1000000; k++) {
            v = k*i+1;
            if (v == 3) continue;
            if (used[v]) continue;
            if (!isPrime(v)) continue;
            if (power(10,gcd(n,v-1),v) != 1) continue;
            used[v] = 1;
            a++;
            s += v;
            if (a == 40) {
                printf("%d\n",s);
                return 0;
            }
        }
    }
    return 0;
}