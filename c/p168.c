//https://projecteuler.net/problem=168
//Number Rotations

#include <stdio.h>
#define N 100

long long modpow(long long a, long long d, long long n) {
    long long res = 1, base = a % n;
    while (d > 0) {
        if (d % 2) res = (res * base) % n;
        base = (base * base) % n;
        d /= 2;
    }
    return (long long)res;
}

int main(void) {
    //let 10a+b be an n-digit number. its right rotation will then be 10^(n-1)*b + a.
    //If 10a + b | b*10^(n-1) + a
    //=> 10a + b | b*10^n + 10*a
    //=> 10a + b | b*10^n + 10*a + b - b
    //=> 10a + b | b(10^n - 1)
    //Thus, we just have to find factors of b(10^n-1) with n digits and = b mod 10
    //10^(n-1)<=10a+b<10^n
    //Let b(10^n - 1) = k(10a+b)
    // => k*10^(n-1) <= k*(10a+b) < k*10^n
    // => k*10^(n-1) <= b(10^n - 1) < k*10^n
    // => b(1 - 1/10^n) < k <= b*(10 - 1/10^(n-1))
    // => b <= k < 10*b
    //This loop does not include 99,999,9999 ... as it breaks when i do mod 10^5
    //Because of this, I add it to S in the beginning itself
    int s = 11101-N; 
    for (int n = 2; n<=N; n++) {
        for (int b = 0; b<10; b++) {
            for (int k = b; k<10*b; k++) {
                if (k%10==9 && (b*(modpow(10,n,k)+k-1))%k == 0) {
                    //last 5 digits
                    int v = modpow(10,n,100000*k);
                    v = (((v+100000*k)*b)%(100000*k))/k;
                    if (v%10 != b) continue;
                    s += v;
                    s %= 100000;
                }
            }
        }
    }
    printf("%d\n", s);
    return 0;
}