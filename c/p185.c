// //https://projecteuler.net/problem=185
// //Number Mind

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define N 16

const char *DATA =
"5616185650518293 ;2 correct\n"
"3847439647293047 ;1 correct\n"
"5855462940810587 ;3 correct\n"
"9742855507068353 ;3 correct\n"
"4296849643607543 ;3 correct\n"
"3174248439465858 ;1 correct\n"
"4513559094146117 ;2 correct\n"
"7890971548908067 ;3 correct\n"
"8157356344118483 ;1 correct\n"
"2615250744386899 ;2 correct\n"
"8690095851526254 ;3 correct\n"
"6375711915077050 ;1 correct\n"
"6913859173121360 ;1 correct\n"
"6442889055042768 ;2 correct\n"
"2321386104303845 ;0 correct\n"
"2326509471271448 ;2 correct\n"
"5251583379644322 ;2 correct\n"
"1748270476758276 ;3 correct\n"
"4895722652190306 ;1 correct\n"
"3041631117224635 ;3 correct\n"
"1841236454324589 ;3 correct\n"
"2659862637316867 ;2 correct\n";

typedef struct Guess {
    char val[N+1];
    int numCorrect;
} Guess;

Guess guesses[256];
int numGuesses = 0;

int heuristic(char num[N+1]) {
    int v = 0;
    for (int i = 0; i<numGuesses; i++) {
        int l = 0;
        for (int j = 0; j<N; j++)
            if (num[j] == guesses[i].val[j]) l++;
        l -= guesses[i].numCorrect;
        if (l<0) l = -l;
        v += l;
    }
    return v;
}

int main(void) {
    int dataLen = 0;
    while (DATA[dataLen++]) {}
    Guess guess;
    while (sscanf(DATA, "%s ;%d correct", guess.val, &guess.numCorrect) == 2) {
        guesses[numGuesses++] = guess;
        DATA += N+12;
    }

    srand(67); //somehow this is the best seed i found for fastest program runtime.
    char ans[N+1] = "1980713417628537"; //random start for annealing

    double T = 200.0;
    double alpha = 0.9999;
    int stagnation = 0;

    while (1) {
        int h1 = heuristic(ans);
        if (h1 == 0) {
            printf("%s\n", ans);
            return 0;
        }
        char new[N+1];
        for (int i = 0; i<=N; i++) new[i] = ans[i];

        int changes = 1 + rand()%3;
        for (int k = 0; k < changes; ++k) {
            int r = rand() % N;
            char v = '0' + (rand() % 10);
            new[r] = v;
        }

        int h2 = heuristic(new);
        int delta = h2 - h1;
        double p = exp(-(double)delta / T);
        double u = (double)rand() / (double)RAND_MAX;
        if (delta <= 0 || u < p) {
            for (int i = 0; i<=N; i++) ans[i] = new[i];
            if (h2 < h1) stagnation = 0;
        } else stagnation++;

        T *= alpha;
        if (T < 1e-6) T = 200.0;
    }
}
