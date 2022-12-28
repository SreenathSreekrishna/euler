//https://projecteuler.net/problem=15
//Lattice paths

#include <stdio.h>

int main(void) {
    int n = 20;
    long double bigFact = 1;
    for (int i = n+1, k = n*2; i<=k; i++) {
        bigFact *= i;
        bigFact /= (i - n);
    }
    printf("%li\n", (long) bigFact);
    return 0;
}