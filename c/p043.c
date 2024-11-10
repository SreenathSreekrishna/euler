//https://projecteuler.net/problem=43
//Sub-string Divisibility

#include <stdio.h>

int arr[] = {0,1,2,3,4,5,6,7,8,9};
long sol = 0;

int f(int a, int b, int c) {
    return a*100+10*b+c;
}

void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void permutations(int a[], int n) {

    for(int i = 0;i < n;i++) {
        swap(a, i, n-1);
        permutations(a, n-1);
        swap(a, i, n-1);
    }

    if (f(a[1],a[2],a[3]) % 2 == 0 && f(a[2],a[3],a[4]) % 3 == 0 && 
        f(a[3],a[4],a[5]) % 5 == 0 && f(a[4],a[5],a[6]) % 7 == 0 && 
        f(a[5],a[6],a[7]) % 11 ==0 && f(a[6],a[7],a[8]) % 13 == 0 && 
        f(a[7],a[8],a[9]) % 17 ==0 && n ==1) {
            long k = 0;
            long p = 1;
            for (int i = 9; i>=0; i--) {
                k += ((long) a[i] * (long) p);
                p *= 10;
            }
            sol += k;
    }
}

int main(void) {
    int digits[10] = {0,1,2,3,4,5,6,7,8,9};
    permutations(arr,10);
    printf("%li\n", sol);
    return 0;
}