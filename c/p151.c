//https://projecteuler.net/problem=151
//A Preference for A5

#include <stdio.h>

float memo[6][6][6][6] = {{{{0}}}};

float markov(int papers[], int depth, int numPapers) {
    //returns expected # of times single paper is found with starting papers 'state' and depth
    if (numPapers == 4 && memo[papers[0]][papers[1]][papers[2]][papers[3]]) {
        return memo[papers[0]][papers[1]][papers[2]][papers[3]];
    }
    float p = numPapers == 1;
    for (int i = 0; i<numPapers; i++) {
        int n = numPapers;
        int pap[numPapers];
        for (int j = 0; j<numPapers; j++) pap[j] = papers[j];
        if (pap[i] == 5) {
            for (int j = i+1; j<n; j++) pap[j-1] = pap[j];
            n--;
        }
        else if (pap[i] == 4) {
            pap[i] = 5;
        }
        else if (pap[i] == 3) {
            pap[i] = 4;
            pap[n++] = 5;
        }
        else if (pap[i] == 2) {
            pap[i] = 3;
            pap[n++] = 4;
            pap[n++] = 5;
        }
        else if (pap[i] == 1) {
            pap[i] = 2;
            pap[n++] = 3;
            pap[n++] = 4;
            pap[n++] = 5;
        }
        if (depth == 0) return p;
        p += markov(pap,depth-1,n)/numPapers;
    }
    if (numPapers == 4) memo[papers[0]][papers[1]][papers[2]][papers[3]] = p;
    return p;
}

int main(void) {
    //Start off with papers {1}. Then on first batch, papers={5,5,4,3,2}
    int papers[32] = {0};
    papers[0] = 1;
    printf("%f\n", markov(papers,16,1)-2);
    return 0;
}