//https://projecteuler.net/problem=67
//Maximum Path Sum II

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *buff;
    FILE *f = fopen("../files/0067_triangle.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!");
        return 1;
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    buff = malloc(len);
    fread(buff, 1, len, f);

    int triangle[100][100] = {{0}};

    int j = 0; 
    int k = 0;
    int l = 0;
    char str[3] = "aa\0";
    for (int i = 0; i<len; i++) {
        if (buff[i] == '\n') {
            l = 0;
            triangle[j][k] = 10*(str[0] - 48) + (str[1] - 48);
            k = 0;
            j++;
            continue;
        }
        if (buff[i] == ' ') {
            l = 0;
            triangle[j][k] = 10*(str[0] - 48) + (str[1] - 48);
            k++;
            continue;
        }
        str[l] = buff[i];
        l++;
    }

    for (int i = 1; i<100; i++) {
        for (int j = 0; j<=i; j++) {
            int parent1 = triangle[i-1][j];
            int parent2 = triangle[i-1][j-1];
            if (parent1 > parent2) {
                triangle[i][j] += parent1;
                continue;
            }
            triangle[i][j] += parent2;
        }
    }

    int max = 0;

    for (int i = 0; i<100; i++) {
        if (triangle[99][i] > max) {
            max = triangle[99][i];
        }
    }
    printf("%d\n", max);

    free(buff);
    return 0;
}