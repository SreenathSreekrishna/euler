//https://projecteuler.net/problem=82
//Path Sum: Three Ways

#include <stdio.h>

long matrix[80][80];
long minPath[80][80];

long min(long a, long b) {
    if (a<b) {
        return a;
    }
    return b;
}

long normalize(int i, int j) {
    if (j<0) {
        return 0;
    }
    if (i<0 || i>79 || j>79) {
        return __INT_MAX__;
    }
    return minPath[i][j];
}

int main(void) {
    FILE *f = fopen("../files/0082_matrix.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!");
        return 1;
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    for (int i = 0; i<80; i++) {
        for (int j = 0; j<79; j++) {
            fscanf(f,"%ld,",&matrix[i][j]);
        }
        fscanf(f,"%ld\n",&matrix[i][79]);
    }

    for (int i = 0; i<80; i++) {
        for (int j = 0; j<80; j++) {
            minPath[i][j] = 0;
        }
    }

    for (int j = 0; j<80; j++) {
        for (int i = 0; i<80; i++) {
            minPath[i][j] = matrix[i][j] + min(normalize(i,j-1), normalize(i-1,j));
        }
        for (int i = 79; i>=0; i--) {
            minPath[i][j] = min(minPath[i][j],matrix[i][j] + normalize(i+1,j));
        }
    }

    long min = __INT_MAX__;
    for (int i = 0; i<80; i++) {
        if (minPath[i][79] < min) {
            min = minPath[i][79];
        }
    }
    printf("%ld\n", min);

    return 0;
}