//https://projecteuler.net/problem=42
//Coded Triangle Numbers

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isTriangular(int n) {
    int s = sqrt(2*n);
    return (s*(s+1) / 2 == n);
}

int wordValue(char *word) {
    int i = 0;
    int s = 0;
    while (word[i] != '\0') {
        s += (word[i] - 64);
        i++;
    }
    return s;
}

int main(void) {
    char *buff;
    FILE *f = fopen("../files/p042_words.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!");
        return 1;
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    buff = malloc(len);
    fread(buff, 1, len, f);

    int q = 0;
    for (int i = 0; i<len; i++) {
        if (buff[i] == '"') {
            q++;
        }
    }
    int numWords = q/2;
    char words[numWords][32];
    char word[32] = {0};
    int idx = 0;
    int wordIdx = 0;
    for (int i = 0; i<len; i++) {
        if (buff[i] == ',') {
            idx = 0;
            for (int i = 0; i<32; i++) {
                words[wordIdx][i] = word[i];
                word[i] = 0;
            }
            wordIdx++;
        }
        if (buff[i] != '"' && buff[i] != ',') {
            word[idx] = buff[i];
            idx++;
        }
    }
    for (int i = 0; i<32; i++) {
        words[numWords-1][i] = word[i];
        word[i] = 0;
    }

    int n = 0;
    for (int i = 0; i<numWords; i++) {
        if (isTriangular(wordValue(words[i]))) n++;
    }

    printf("%d\n", n);

    free(buff);
    return 0;
}