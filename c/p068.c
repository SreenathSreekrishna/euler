//https://projecteuler.net/problem=68
//Magic 5-gon Ring

#include <stdio.h>

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int isCompatible(int arr1[5], int arr2[5]) {
    int c = arr1[0] + arr2[0] + arr2[1];
    for (int i = 1; i<5; i++) {
        if (c != arr1[i] + arr2[i] + arr2[(i+1)%5]) {
            return 0;
        }
    }
    return 1;
}

long long normalize(int arr1[5], int arr2[5]) {
    int idx;
    long long s = 0;
    for (int i = 0; i<5; i++) {
        if (arr1[i] == 6) {
            idx = i;
        }
    }
    for (int i = idx; i < idx+5; i++) {
        if (arr1[i%5] == 10) {
            s*=10;
        }
        s += arr1[i%5];
        s *= 10;
        s += arr2[i%5];
        s*= 10;
        s += arr2[(i+1)%5];
        s*=10;
    }
    return s/10;
}

void permuteRec(int* arr, int idx, int n, int *index, int storage[120][5]) {
    if (idx == n - 1) {
        for (int j = 0; j<n; j++) {
            storage[*index][j] = arr[j];
        }
        (*index)++;
        return;
    }

    for (int i = idx; i < n; i++) {
        swap(&arr[idx], &arr[i]);
        permuteRec(arr, idx + 1, n, index, storage);
        swap(&arr[idx], &arr[i]);
    }
}

int main(void) {
    //note that if there is a 16-digit arring, it means that the 10 must be on one of the five outer numbers
    //logically, the largest numbers must be on the outside, so as to minimize the common sum
    int outer[5] = {6,7,8,9,10};
    int inner[5] = {1,2,3,4,5};

    int innerPerms[120][5];
    int outerPerms[120][5];

    int i = 0;
    
    permuteRec(outer,0,5, &i, outerPerms);
    i = 0;
    permuteRec(inner,0,5, &i, innerPerms);

    long long max = 0;

    for (int i = 0; i<120; i++) {
        for (int j = 0; j<120; j++) {
            if (isCompatible(outerPerms[j],innerPerms[i])) {
                long long n = normalize(outerPerms[j], innerPerms[i]);
                if (n > max) {
                    max = n;
                }
            }
        }
    }

    printf("%lld\n", max);
    return 0;
}