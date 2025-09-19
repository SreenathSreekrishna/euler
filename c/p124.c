//https://projecteuler.net/problem=124
//Ordered Radicals

#include <stdio.h>

typedef struct radical {
    int n;
    int r;
} radical;

int rad(int n) {
    int r = 1;
    while (n>1) {
        for (int i = 2; i <= n; i++) {
            if (n % i != 0) continue;
            r *= i;
            while (n % i == 0) {
                n /= i;
            }
            break;
        }
    }
    return r;
}

void merge(radical a[], int l, int m, int r) {
    int l1 = m - l + 1;
    int l2 = r - m;
    radical left[l1], right[l2];
    
    for (int i = 0; i<l1; i++) left[i] = a[l+i];
    for (int i = 0; i<l2; i++) right[i] = a[m+i+1];
    
    int i = 0;
    int j = 0;
    int k = l;
    
    while (i<l1 && j<l2) {
        if (left[i].r <= right[j].r) {
            a[k] = left[i];
            i++;
        }
        else {
            a[k] = right[j];
            j++;
        }
        k++;
    }
    
    while (i < l1) {
        a[k] = left[i];
        i++;
        k++;
    }
    while (j < l2) {
        a[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(radical a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main(void) {
    radical r[100000];
    for (int i = 1; i<=100000; i++) {
        radical ra;
        ra.n = i;
        ra.r = rad(i);
        r[i-1] = ra;
    }
    mergeSort(r,0,99999);
    printf("%d\n", r[9999].n);
    return 0;
}