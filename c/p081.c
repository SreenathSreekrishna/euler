//https://projecteuler.net/problem=81
//Path Sum: Two Ways

#include <stdio.h>

int main(void) {
    FILE *f = fopen("../files/0081_matrix.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!");
        return 1;
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    int matrix[80][80];
    for (int i = 0; i<80; i++) {
        for (int j = 0; j<79; j++) {
            fscanf(f,"%d,",&matrix[i][j]);
        }
        fscanf(f,"%d\n",&matrix[i][79]);
    }

    for (int i = 0; i<80; i++) {
        for (int j = 0; j<80; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (i == 0) {
                matrix[i][j] += matrix[i][j-1];
                continue;
            }
            if (j == 0) {
                matrix[i][j] += matrix[i-1][j];
                continue;
            }
            if (matrix[i-1][j] < matrix[i][j-1]) {
                matrix[i][j] += matrix[i-1][j];
            }
            else {
                matrix[i][j] += matrix[i][j-1];
            }
        }
    }
    printf("%d\n", matrix[79][79]);
    return 0;
}