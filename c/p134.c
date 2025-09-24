//https://projecteuler.net/problem=134
//Prime Pair Connection

#include <stdio.h>

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

int main(void) {
    //k*10^d + p1 = 0 mod p2 (d is number of digits of p1)
    //k = -p1/10^d mod p2
    int p1 = 0;
    short IS_PRIME[1000004] = {0};
    long long sum = 0;
    for (int p2 = 2; p2<  1000004; p2++) {
        if (!IS_PRIME[p2]) {
            for (int j = 2; p2 * j< 1000004; j++)
                IS_PRIME[p2 * j]= 1;
            if (!p1 || p2<=5) {p1 = p2; continue;}
            int d = 0;
            int tmp = p1;
            while (tmp) {
                d++;
                tmp /= 10;
            }
            //calculate -p1/10^d mod p2 = -p1*10^(d(p2-2)) mod p2
            long long k = -p1*(long)power(10,d*(p2-2),p2);
            k += (-k/p2+1)*p2;
            for (int l = 0; l<d; l++) k*=10;
            k += p1;
            sum += k;
            p1 = p2;
        }
    }
    printf("%lld\n", sum);
    return 0;
}