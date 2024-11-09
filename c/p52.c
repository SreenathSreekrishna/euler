//https://projecteuler.net/problem=52
//Permuted Multiples

#include <stdio.h>

int intSort(int n) {
    //sorts an integer n
    int frequency[10] = {0};
    while (n!=0) {
        frequency[n % 10]++;
        n = n / 10;
    }
    int t = 0;
    int p = 1;
    for (int i = 0; i<10; i++) {
        for (int j = 0; j<frequency[i]; j++) {
            t+=p*i;
            p*=10;
        }
    }
    return t;
}

int main(void) {
    int n = 1;
    while (1) {
        int nSort = intSort(n);
        int valid = 1;
        for (int i = 2; i<7; i++) {
            valid = valid && (intSort(i*n) == nSort);
        }
        if (valid) {
            printf("%d\n", n);
            return 0;
        }
        n++;
    }
}