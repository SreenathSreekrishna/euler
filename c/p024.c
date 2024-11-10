//https://projecteuler.net/problem=24
//Lexicographic Permutations

#include <stdio.h>

int main(void) {
    //https://en.wikipedia.org/wiki/Factorial_number_system#Permutations
    int n = 999999;
    int factoradic[11] = {0};
    for (int i = 1; i<11; i++) {
        factoradic[i] = n%i;
        n /= i;
    }
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    int res[10] = {0};
    for (int i = 10; i>0; i--) {
        int idx = factoradic[i];
        res[10-i] = arr[idx];
        for (int j = idx; j<10; j++) {
            arr[j] = arr[j+1];
        }
    }
    for (int i = 0; i<10; i++) {
        printf("%d", res[i]);
    }
    printf("\n");
    return 0;
}