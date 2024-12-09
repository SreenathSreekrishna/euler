//https://projecteuler.net/problem=87
//Prime Power Triples

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n <= 3) {
        return 1;
    }
    for (int i = 2; i<sqrt((float) n)+1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int *expressible = calloc(50000000,sizeof(int));
    int count = 0;
    for (int i = 1; i<84; i++) {
        if (!isPrime(i)) {
            continue;
        }
        for (int j = 1; j<368; j++) {
            if (!isPrime(j)) {
                continue;
            }
            for (int k = 1; k<7072; k++) {
                if (!isPrime(k)) {
                    continue;
                }
                int v = k*k + j*j*j + i*i*i*i;
                if (v >= 50000000) {
                    continue;
                }
                if (expressible[v]) {
                    continue;
                }
                expressible[v] = 1;
                count++;
            }
        }
    }
    printf("%d\n", count);
    free(expressible);
    return 0;
}