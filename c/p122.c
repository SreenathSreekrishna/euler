//https://projecteuler.net/problem=122
//Efficient Exponentiation

#include <stdio.h>
#include <math.h>

int m[201] = {0};

void getAllChains(int arr[12], int chainLen) {
    if (chainLen >= 12) return;
    for (int i = 0; i<chainLen; i++) {
        arr[chainLen] = arr[chainLen-1] + arr[i];
        if (arr[chainLen] <=200) {
            if (!m[arr[chainLen]]) m[arr[chainLen]] = chainLen;
            else if (chainLen<m[arr[chainLen]]) m[arr[chainLen]] = chainLen;
        }
        getAllChains(arr, chainLen+1);
    }
}
int main(void) {
    int s = 0;
    int arr[12];
    arr[0] = 1;
    getAllChains(arr,1);
    for (int i = 0; i<=200; i++) s+=m[i];
    printf("%d\n", s);
    return 0;
}