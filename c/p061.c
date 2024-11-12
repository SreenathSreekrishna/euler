//https://projecteuler.net/problem=61
//Cyclical Figurate Numbers

#include <stdio.h>
#include <math.h>

int isPolygonal(int n, int x) {
    //checks if x is an n-gonal number
    //y((n-2)y-(n-4))/2 is an n-gonal number, if y is an integer

    int y = (n-4+sqrt(n*n + 8*n*(x-1)-16*(x-1)))/(2*n-4);
    return (y*((n-2)*y-(n-4))/2 == x);
}

int doRecursion(int prevValue,int n,int used[9], int sol[6]) {
    if (n == 0) {
        if (sol[0] / 100 != sol[5] % 100) {
            return 0;
        }
        int s = 0;
        for (int i = 0; i<6; i++) {
            s += sol[i];
        }
        printf("%d\n",s);
        return 0;
    }
    int digits = (prevValue % 100);
    int start = digits * 100;
    int end = start + 100;
    if (n == 6) {
        start = 1000;
        end = 5000; //no cyclic things
    }
    if (start < 1000) {
        return 0;
    }
    for (int i = start; i<end; i++) {
        int newUsed[9];
        for (int i = 0; i<9; i++) {
            newUsed[i] = used[i];
        }
        int pass = 0;
        for (int t = 3; t<9; t++) {
            if (used[t]) {
                continue;
            }
            if (isPolygonal(t,i)) {
                pass = 1;
                newUsed[t] = 1;
                break;
            }
        }
        if (!pass) {
            continue;
        }
        sol[6-n] = i;
        doRecursion(i,n-1,newUsed,sol);
    }
    return 0;
}

int main(void) {
    int sol[6] = {0};
    int used[9] = {0};
    doRecursion(-1,6,used,sol);
    return 0;
}