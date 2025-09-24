//https://projecteuler.net/problem=133
//Repunit Nonfactors

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

int check(int k, int n) {
    //finds a k' < k such that 10^k' = 1 mod n
    for (int i = 2; i<k; i++) {
        if (k%i == 0 && power(10,k/i,n) == 1) {
            return check(k/i,n);
        }
    }
    return k;
}

int A(int n) {
    //least k such that 10^k = 1 mod n
    return check(n-1,n);
}

int main(void) {
    //10^(10^n) != 1 mod p for all n, p>5 as we already know 2,3,5 are nonfactors
    //=> A(p) is not a factor of 10^n for all n => A(p) contains factors other than 2,5
    long sum = 10;
    int IS_PRIME[100000] = {0};
    for (int i = 2; i<  100000; i++) {
        if (!IS_PRIME[i]) {
            for (int j = 2; i * j< 100000; j++)
                IS_PRIME[i * j]= 1;
            if (i == 2 || i == 3 || i == 5) continue;
            int n = A(i);
            while (n%2 == 0) n/=2;
            while (n%5 == 0) n/=5;
            if (n!=1) sum+=i;
        }
    }
    printf("%ld\n",sum);
    return 0;
}