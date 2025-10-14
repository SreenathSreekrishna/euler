//https://projecteuler.net/problem=160
//Factorial Trailing Digits

#include <stdio.h>

long long modpow(long long a, long long d, long long n) {
    long long res = 1, base = a % n;
    while (d > 0) {
        if (d % 2) res = (res * base) % n;
        base = (base * base) % n;
        d /= 2;
    }
    return (long long)res;
}

long table5[3125];
long table2[32];

long f2(long n) {
    if (n<2) return 1;
    long long val = table2[n%32];
    return (val*f2(n/2))%32;
}

long f5(long n) {
    if (n<5) return table5[n];
    //product of values coprime to 5 from 1 to 3125 is 3124.
    long long val = (modpow(3124, n/3125, 3125) * table5[n%3125]) % 3125;
    return (val*f5(n/5))%3125;
}

int main(void) {
    //the problem is just finding n! mod 10^5 after removing all factors of 5
    //and an equal number of factors of 2. we can do this by first computing n! mod 10^5
    //removing all factors of 2 and 5 and then multiplying again by the remaining factors of 2
    //later on. Thus, we compute n! mod 100000 with all factors of 2 and 5 removed first.
    //This can be done using crt.
    long n = 1e12;
    long v2 = 0;
    long v5 = 0;
    long m = n; while (m>0) v2 += (m /= 2);
    m = n; while (m>0) v5 += (m /= 5);
    long pow2 = v2-v5;

    table5[0] = 1;
    for (int i = 1; i<3125; i++) {
        long v = (i%5 == 0) ? 1 : i;
        table5[i] = (table5[i-1]*v)%3125;
    }
    table2[0] = 1;
    for (int i = 1; i<32; i++) {
        long v = (i%2 == 0) ? 1 : i;
        table2[i] = (table2[i-1]*v)%32;
    }

    long inv2 = modpow(2, 2499, 3125);
    long inv5 = modpow(5, 15, 32);
    long val2 = (f2(n)*modpow(inv5, v5, 32))%32;
    long val5 = (f5(n)*modpow(inv2, v2, 3125))%3125;
    long ans = 32*(((val5 - val2)*modpow(32, 2499,3125))%3125) + val2;
    ans *= modpow(2, pow2, 100000);
    ans %= 100000;
    printf("%ld\n", ans);
    return 0;
}