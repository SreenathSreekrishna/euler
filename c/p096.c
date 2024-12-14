//https://projecteuler.net/problem=96
//Su Doku

#include <stdio.h>

int solved[9][9];

int solve(int sudoku[9][9]) {
    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            if (sudoku[i][j]) {
                continue;
            }
            int freq[10] = {0};
            for (int a = 0; a<9; a++) {
                freq[sudoku[a][j]]++;
            }
            for (int b = 0; b<9; b++) {
                freq[sudoku[i][b]]++;
            }
            int a = (i/3) * 3;
            int b = (j/3) * 3;
            for (int m = 0; m<3; m++) {
                for (int n = 0; n<3; n++) {
                    freq[sudoku[a+m][b+n]]++;
                }
            }
            for (int a = 1; a<10; a++) {
                if (!freq[a]) {
                    sudoku[i][j] = a;
                    if (solve(sudoku)) {
                        for (int i = 0; i<9; i++) {
                            for (int j = 0; j<9; j++) {
                                solved[i][j] = sudoku[i][j];
                            }
                        }
                        return 1;
                    }
                }
            }
            sudoku[i][j] = 0;
            return 0;
        }
    }
    return 1;
}

int main(void) {
    FILE *f = fopen("../files/p096_sudoku.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    int puzzles[50][9][9];

    for (int i = 0; i<50; i++) {
        char n[10];
        fscanf(f,"Grid%s\n",&n[0]);
        for (int j = 0; j<9; j++) {
            char line[10];
            fscanf(f,"%s\n",&line[0]);
            for (int k = 0; k<9; k++) {
                puzzles[i][j][k] = (int) line[k] - 48;
            }
        }
    }
    
    int s = 0;
    for (int i = 0; i<50; i++) {
        solve(puzzles[i]);
        s += solved[0][0]*100+solved[0][1]*10+solved[0][2];
    }

    printf("%d\n", s);

    return 0;
}