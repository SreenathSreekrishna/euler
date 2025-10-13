//https://projecteuler.net/problem=156
//Counting Digits

#include <stdio.h>

long f(long n, int d) {
    //notice that f(10^k-1, d) = k*10^(k-1)
    //f(a*10^k + b, d) = f(b, d) + a*k*10^(k-1) + c
    //if a=d, c=b+1
    //if a>d, c = 10^k
    //else c = 0

    if (n == 0) return 0;
    long m = n;
    long p = 1;
    int k = 0;
    while (m > 9) {
        p *= 10;
        m /= 10;
        k++;
    }
    int a = m%10;
    long b = n - a*p;
    long ret = f(b,d) + a*k*p/10;
    if (a == d) ret += b+1;
    else if (a>d) ret += p;
    return ret;
}

long sum = 0;

void search(long l, long r, int d) {
    if (l == r && f(l,d) == l) {
        sum += l;
        return;
    }
    long m = (l+r)/2;
    if (f(l,d) <= m && f(m,d) >= l) {
        search(l,m,d);
    }
    if (f(m+1,d) <= r && f(r,d) >= m+1) {
        search(m+1,r,d);
    }
}

int main(void) {
    for (int d = 1; d<=9; d++) {
        search(0,1000000000000,d);
    }
    printf("%ld\n", sum);
    return 0;
}
