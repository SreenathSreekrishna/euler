//https://projecteuler.net/problem=105
//Special Subset Sums: Testing

#include <stdio.h>

int checkSpecialSum(int nums[12], int length) {
    int powers[13] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096};
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += nums[i];
    }
    int sums[sum+1];
    for (int i = 0; i<=sum; i++) {
        sums[i] = 0;
    }
    for (int i = 1; i<powers[length]; i++) {
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

int main(void) {
    FILE *f = fopen("../files/p105_sets.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
    int nums[100][12];
    int lengths[100];
    for (int i = 0; i<100; i++) {
        fscanf(f,"%d",&nums[i][0]);
        int j = 1;
        while (fscanf(f,",%d",&nums[i][j]) == 1) {
            j++;
        }
        fseek(f,1,SEEK_CUR);
        lengths[i] = j;
    }
    int sum = 0;
    for (int i = 0; i<100; i++) {
        if (checkSpecialSum(nums[i], lengths[i])) {
            for (int j = 0; j<lengths[i]; j++) {
                sum += nums[i][j];
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}