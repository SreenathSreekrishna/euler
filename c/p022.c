//https://projecteuler.net/problem=22
//Names Scores

#include <stdio.h>
#include <stdlib.h>

int cmp (char name1[16], char name2[16]) {
    for (int i = 0; i<16; i++) {
        if (name1[i] > name2[i]) {
            return -1;
        }
        if (name1[i] < name2[i]) {
            return 1;
        }
    }
    return 0;
}

int getLetterScore(char name[16]) {
    int s = 0;
    for (int i = 0; i<16; i++) {
        if (name[i]) {
            s += ((int) name[i] - 64);
        }
    }
    return s;
}

int main(void) {
    char *buff;
    FILE *f = fopen("../files/p022_names.txt", "r");
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
    int numNames = q/2;
    char names[numNames][16];
    char name[16] = {0};
    int idx = 0;
    int nameIdx = 0;
    for (int i = 0; i<len; i++) {
        if (buff[i] == ',') {
            idx = 0;
            for (int i = 0; i<16; i++) {
                names[nameIdx][i] = name[i];
                name[i] = 0;
            }
            nameIdx++;
        }
        if (buff[i] != '"' && buff[i] != ',') {
            name[idx] = buff[i];
            idx++;
        }
    }
    for (int i = 0; i<16; i++) {
        names[numNames-1][i] = name[i];
        name[i] = 0;
    }

    int s = 0;

    for (int i = 0; i<numNames; i++) {
        int a = 0;
        for (int j = 0; j<numNames; j++) {
            if (cmp(names[i], names[j]) == -1) {
                a++;
            }
        }
        s += (a+1)*getLetterScore(names[i]);
    }

    printf("%d\n", s);

    free(buff);
    return 0;
}