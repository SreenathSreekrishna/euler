//https://projecteuler.net/problem=118
//Pandigital Prime Sets

#include <stdio.h>
#include <math.h>

int count = 0;

int nums[9] = {1,2,3,4,5,6,7,8,9};

int isPrime(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    for (int i = 2; i<sqrt(n)+1; i++) if (n % i == 0) return 0;
    return 1;
}

int convert(int arr[], int len) {
    int val = 0;
    int p = 1;
    for (int i = len-1; i>=0; i--) {
        val += arr[i] * p;
        p *= 10;
    }
    return val;
}

void getAllParts(int arr[9], int numPartsLeft, int leftover, int idx) {
    if (numPartsLeft == 1) {
        int k = 0;
        int primes[9] = {0};
        int pcount = 0;
        for (int i = 0; i<idx; i++) {
            int num[9] = {0};
            for (int j = 0; j<arr[i]; j++)  {
                num[j] = nums[k];
                k++;
            }
            int v = convert(num,arr[i]);
            if (isPrime(v)) primes[pcount++] = v;
            else return;
        }
        int num[9] = {0};
        for (int l = 0; l<leftover; l++) {
            num[l] = nums[k+l];
        }
        int v = convert(num,leftover);
        if (isPrime(v)) primes[pcount++] = v;
        else return;
        for (int i = 0; i<pcount-1; i++) if (primes[i] < primes[i+1]) return;
        count++;
        return;
    }
    for (int i = 1; i<leftover; i++) {
        arr[idx] = i;
        getAllParts(arr,numPartsLeft - 1,leftover-i,idx+1);
    }
}

void swap(int *x, int *y) {
    int tmp; 
    tmp = *x; 
    *x = *y; 
    *y = tmp; 
}

void permute(int *a, int l, int r) {
    int i;
    if (l == r) {
        for (int size = 2; size<7; size++) {
            int arr[size];
            getAllParts(arr,size,9,0);
        }
        return;
    }
    for (i = l; i <= r; i++) {
        swap((a + l), (a + i));
        permute(a, l + 1, r);
        swap((a + l), (a + i));
    }
}

int main(void) {
    permute(nums,0,8);
    printf("%d\n", count);
    return 0;
}