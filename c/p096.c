//https://projecteuler.net/problem=96
//Su Doku

#include <stdio.h>

int main(void) {
    FILE *f = fopen("../files/p096_sudoku.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
}