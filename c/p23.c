//https://projecteuler.net/problem=23
//Non-Abundant Sums

#include <stdio.h>
#include <stdlib.h>

int abundant(int n) {
    int s = 0;
    for (int i = (n/2); i>0; i--) {
        if (n % i == 0) {
            s += i;
        }
        if (s > n) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int abundants[28124];
    int numAbundants = 0;
    for (int i = 1; i<28124; i++) {
        if (abundant(i)) {
            abundants[numAbundants] = i;
            numAbundants++;
        }
    }

    int *sumAbundants = malloc(numAbundants*numAbundants*sizeof(int));
    int canBeExpressed[56248] = {0};
    for (int i = 0; i<numAbundants; i++) {
        for (int j = 0; j<numAbundants; j++) {
            int v = abundants[i] + abundants[j];
            sumAbundants[i*numAbundants+j] = v;
            canBeExpressed[v] = 1;
        }
    }

    int s = 0;
    for (int i = 0; i<28124; i++) {
        if (!canBeExpressed[i]) {
            s += i;
        }
    }
    printf("%d\n", s);
    free(sumAbundants);
    return 0;
}