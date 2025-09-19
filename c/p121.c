//https://projecteuler.net/problem=121
//Disc Game Prize Fund

#include <stdio.h>
#define n 15

float p = 0;

void getCombinations(int mask[n], int numLeft, int idx) {
    if  (idx == n) {
        if (numLeft != 0) return;
        float l = 1;
        for (int i = 0; i<idx; i++) {
            if (mask[i]) l /= (float) (i+2);
            else l *= (1-(float) 1/(float) (i+2));
        }
        p += l;
        return;
    }
    mask[idx] = 1;
    getCombinations(mask, numLeft-1, idx+1);
    mask[idx] = 0;
    getCombinations(mask, numLeft, idx+1);
}

int main(void) {
    //prize fund = 1/probability
    for (int i = n/2 + 1; i<=n; i++) {
        int mask[n] = {0};
        getCombinations(mask,i,0);
    }
    printf("%d\n", (int) (1/p));
    return 0;
}