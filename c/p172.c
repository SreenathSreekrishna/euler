//https://projecteuler.net/problem=172
//Few Repeated Digits

#include <stdio.h>

int freq[10] = {0};

long long factorial(int n) {
    long v = 1;
    for (int i = 2; i<=n; i++) v *= i;
    return v;
}

long count(int remainingDigits, int lastAdded) {
    if (freq[lastAdded] >= 4) return 0;
    if (!remainingDigits) {
        long long val = factorial(18);
        for (int i = 0; i<10; i++) val /= factorial(freq[i]);
        if (freq[0]) {
            long long val2 = factorial(17) / factorial(freq[0]-1);
            for (int i = 1; i<10; i++) val2 /= factorial(freq[i]);
            val -= val2;
        }
        return val;
    }
    long s = 0;
    for (int i = lastAdded; i<=9; i++) {
        freq[i]++;
        s += count(remainingDigits-1, i);
        freq[i]--;
    }
    return s;
}

int main(void) {
    printf("%ld\n", count(18,0));
    return 0;
}