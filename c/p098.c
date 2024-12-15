//https://projecteuler.net/problem=98
//Anagramic Squares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int isSquare(long n) {
    long s = sqrt(n);
    return s*s == n;
}

long mapping(const char *a, const char *b, long n) {
    int map[26] = {0};
    for (int i = strlen(a)-1; i>=0; i--) {
        map[(int) a[i] - 65] = n % 10;
        n /= 10;
        if (n == 0 && i != 0) {
            return -1;
        }
    }
    long r = 0;
    for (int i = 0; b[i]; i++) {
        r *= 10;
        r += map[b[i] - 65];
        if (i == 0 && r == 0) {
            return -1;
        }
    }
    return r;
}

int works(const char *a, long n) {
    int usedNums[10] = {0};
    int map[26] = {0};
    for (int i = strlen(a)-1; i>=0; i--) {
        if (map[(int) a[i] - 65]) {
            if (map[(int) a[i] - 65] != n%10) return 0;
        }
        if (usedNums[n%10]) {
            return 0;
        }
        map[(int) a[i] - 65] = n % 10;
        usedNums[n%10] = 1;
        n /= 10;
        if (n == 0 && i != 0) {
            return 0;
        }
    }
    if (n != 0) {
        return 0;
    }
    return 1;
}

int main (void) {
    FILE *f = fopen("../files/p098_words.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    char *buff = malloc(len);
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

    int frequencies[numWords][26];
    for (int i = 0; i<numWords; i++) {
        int j = 0;
        while (words[i][j]) {
            frequencies[i][(int) words[i][j] - 65]++;
            j++;
        }
    }

    long max = -1;

    for (int i = 0; i<numWords; i++) {
        for (int j = i+1; j<numWords; j++) {
            int eq = 1;
            int s = 0;
            for (int k = 0; k<26; k++) {
                if (frequencies[i][k] != frequencies[j][k]) {
                    eq = 0;
                    break;
                }
                s += frequencies[i][k];
            }
            if (!eq) continue;
            for (int k = 1; k<1000000; k++) {
                if (!works(words[i],(long) k*k)) continue;
                long sol = mapping(words[i], words[j], k*k);
                if (!isSquare(sol) || sol == (long) k*k) {
                    continue;
                }
                if ((long) k*k > sol) {
                    sol = (long) k*k;
                }
                if (sol > max) {
                    max = sol;
                }
            }
        }
    }

    printf("%ld\n",max);

    free(buff);
    return 0;
}