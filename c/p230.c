//https://projecteuler.net/problem=230
//Fibonacci Words

#include <stdio.h>
#define A "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
#define B "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"
#define N 100

unsigned long long fib[100] = {0,1};

int find(unsigned long long n, int k) {
    //finds index n in F_k
    if (k == 1) return 0;
    if (k == 2) return 1;
    if (n < fib[k-2]) return find(n, k-2);
    return find(n-fib[k-2], k-1);
}

int F(unsigned long long n) {
    //finds the nth element (0 for A, 1 for B) in the fibonacci word whose length first exceeds n
    //for e.g. if n=9, the sequence is 0,1,01,101,01101,10101101,0110110101101
    //thus the first element that exceeds length 9 is 0110110101101, which has 1 at index 9, so F(9)=1
    if (n == 0) return 0;
    if (n == 1) return 1;
    int len = 0;
    while (fib[len] <= n) len++;
    return find(n,len);
}

int D(unsigned long long n) {
    n--;
    int idx = n % N;
    n /= N;
    if (F(n)) return B[idx];
    return A[idx];
}

int main(void) {
    for (int i = 2; i<100; i++) fib[i] = fib[i-1]+fib[i-2];
    char ans[19] = {0};
    unsigned long long pow7 = 1;
    for (int i = 0; i<=17; i++) {
        ans[17-i] = D((unsigned long long) (127+19*i) * pow7);
        pow7 *= 7;
    }
    printf("%s\n", ans);
    return 0;
}