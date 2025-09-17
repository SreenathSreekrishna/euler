//https://projecteuler.net/problem=111
//Primes with Runs

#include <stdio.h>
#include <math.h>
#define numLen 10

int isPrime(long n) {
    for (int i = 2; i<sqrt(n)+1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

long convert(int num[numLen]) {
    long p = 1;
    long v = 0;
    for (int i = 0; i<numLen; i++) {
        v += (long) num[i] * p;
        p *= 10;
    }
    return v;
}

int main(void) {
    long sum = 0;
    int leftover[10] = {0}; //numbers for which 9 digit runs are impossible
    int leftlen = 1;
    for (int l = 1; l<10; l++) {
        int N = 0;
        for (int i = 0; i<10; i++) {
            for (int j = 0; j<numLen-!i; j++) {
                int num[numLen];
                for (int k = 0; k<numLen; k++) num[k] = l;
                num[j] = i;
                long n = convert(num);
                if (!isPrime(n)) continue;
                N++;
                sum += n;

            }
        }
        if (!N) leftover[leftlen++] = l;
    }

    for (int l = 0; l<leftlen; l++) {
        int d = leftover[l];
        for (int i = 0; i<100; i++) {
        for (int a = 0; a<numLen; a++) {
        for (int b = 0; b<a; b++) {
            int num[numLen];
            for (int k = 0; k<numLen; k++) num[k] = d;
            num[a] = i/10;
            num[b] = i%10;
            if (num[numLen-1] == 0) continue;
            long n = convert(num);
            if (isPrime(n)) sum += n;
        }}}
    }

    printf("%li\n", sum);
    return 0;
}