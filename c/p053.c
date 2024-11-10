//https://projecteuler.net/problem=53
//Combinatoric Selections

#include <stdio.h>

int exceedsMill(int n) {
    //returns the number of 0<=r<=n s.t. nCr > 1000000
    for (int r = 1; r<n; r++) {
        long v = 1;
        for (int k = n; k>n-r; k--) {
            v *= k;
        }
        for (int k = 1; k<=r; k++) {
            v /= k;
        }
        if (v>1000000) {
            return n-2*r+1;
        }
    }
    return 0;
}

int main(void) {
    int s = 0;
    for (int i = 3; i<=100; i++) {
        s += exceedsMill(i);
    }
    printf("%d\n",s);
}