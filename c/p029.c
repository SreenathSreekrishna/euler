//https://projecteuler.net/problem=29
//Distinct Powers

#include <stdio.h>
#include <stdlib.h>
#define PRIME_FACTORIZATION_SIZE 1024
#define BOUND 100

int main(void) {
    int **terms = malloc(sizeof(int *) * (BOUND - 1) * (BOUND - 1));
    for (int i = 0; i<(BOUND - 1)*(BOUND - 1); i++) {
        terms[i] = malloc(sizeof(int) * PRIME_FACTORIZATION_SIZE);
    }
    int idx = 0;
    for (int i = 2; i<=BOUND; i++) {
        for (int j = 2; j<=BOUND; j++) {
            int v[PRIME_FACTORIZATION_SIZE] = {-1};
            int k = i;
            int id = 0;
            while (k > 1) {
                for (int l = 2; l<=k; l++) {
                    if (k % l == 0) {
                        for (int m = 0; m<j; m++) {
                            v[id+m] = l;
                        }
                        k /= l;
                        id += j;
                        break;
                    }
                }
            }
            int found = 0;
            for (int l = 0; l<idx; l++) {
                int m;
                int eq = 1;
                for (m = 0; m<PRIME_FACTORIZATION_SIZE; m++) {
                    if (terms[l][m] != v[m]) {
                        eq = 0;
                        break;
                    }
                }
                if (m == PRIME_FACTORIZATION_SIZE && eq) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                for (int l = 0; l<PRIME_FACTORIZATION_SIZE; l++) {
                    terms[idx][l] = v[l];
                }
                idx++;
            }
        }
    }
    printf("%d\n", idx);
    for (int i = 0; i<(BOUND - 1)*(BOUND - 1); i++) {
        free(terms[i]);
    }
    free(terms);
    return 0;
}