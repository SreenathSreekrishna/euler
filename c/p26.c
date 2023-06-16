//https://projecteuler.net/problem=26
//Reciprocal Cycles

#include <stdio.h>

int terminating(int n) {
    //returns a value telling whether the decimal expansion of 1/n will be terminating
    while (n != 1) {
        for (int i = 2; i<=n; i++) {
            if (n % i == 0) {
                if (i != 2 && i != 5) {
                    return 0;
                }
                n = n / i;
                break;
            }
        }
    }
    return 1;
}

int getCycle(int n) {
    //outputs the length of the cycle of 1/n
    if (terminating(n)) {
        return 0;
    }
    int k = 1;
    int modulos[1024] = {-1};
    int i = 0;
    while (1) {
        int v = k % n;
        for (int j = 0; j<1024; j++) {
            if (modulos[j] == v) {
                return i-j;
            }
        }
        modulos[i] = v;
        k = v * 10;
        i++;
    }
}

int main(void) {
    int max = -1;
    int maxNum = -1;
    for (int i = 1; i<1000; i++) {
        int v = getCycle(i);
        if (v > max) {
            max = v;
            maxNum = i;
        }
    }
    printf("%d\n", maxNum);
    return 0;
}