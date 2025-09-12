//https://projecteuler.net/problem=103
//Special Subset Sums: Optimum

#include <stdio.h>
#define K 7
#define POWK 128

int DONE = 0;

int checkSpecialSum(int nums[K]) {
    int sum = 0;
    for (int i = 0; i < K; i++) {
        sum += nums[i];
    }
    int sums[sum+1];
    for (int i = 0; i<=sum; i++) {
        sums[i] = 0;
    }
    for (int i = 1; i<POWK; i++) {
        int s = 0;
        int j = 0;
        int cardinality = 0;
        int num = i;
        while (num) {
            if (num%2) {
                s += nums[j];
                cardinality++;
            }
            j++;
            num /= 2;
        }
        if (sums[s]) {
            return 0;
        }
        else {
            sums[s] = cardinality;
        }
    }
    int a = -1;
    for (int i = 0; i<=sum; i++) {
        if (sums[i] == 0) continue;
        if (a == -1) {
            a = sums[i];
            continue;
        }
        if (sums[i] < a) {
            return 0;
        }
        a = sums[i];
    }
    return 1;
}

void generate(int n, int k, int start, int chosen[], int index) {
    if (k == 0 && n == 0 && index == K) {
        int check = checkSpecialSum(chosen);
        DONE |= check;
        if (check) {
            for (int i = 0; i<K; i++) {
                printf("%d", chosen[i]);
            }
            printf("\n");
        }
        return;
    }
    if (k == 0 || n <= 0 || index >= K) return;

    for (int i = start; i <= n; i++) {
        if (index == 0 && i<20) continue;
        chosen[index] = i;
        generate(n - i, k - 1, i + 1, chosen, index + 1);
    }
}


int main(void) {
    int sum = 161;
    while (!DONE) {
        int chosen[K];
        generate(sum, K, 1, chosen, 0);
        sum++;
    }
}