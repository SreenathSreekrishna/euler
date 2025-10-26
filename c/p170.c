//https://projecteuler.net/problem=170
//Pandigital Concatenating Products

#include <stdio.h>
#include <stdlib.h>

int nums[10] = {0,1,2,3,4,5,6,7,8,9};
int currfreq[10] = {0};
long currmult = 0;
long currNumbers[10] = {0};
long ans = 0;

int cmp(const void *a, const void *b) {
    char *x = (char *) a; char *y = (char *) b;
    for (int i = 0; i<10; i++) {
        if (x[i] > y[i]) return -1;
        if (x[i] < y[i]) return 1;
    }
    return 0;
}

long convert(int arr[], int len) {
    long val = 0;
    for (int i = 0; i<len; i++) {
        val *= 10;
        val += arr[i];
    }
    return val;
}

void restore(long n) {
    if (n == 0) currfreq[0]--;
    while (n>0) {
        currfreq[n%10]--;
        n /= 10;
    }
}

int checkDuplicates(long n) {
    //0 if duplicates exist eg 12344
    //1 if no duplicates eg 12345
    if (n == 0) currfreq[0] ++;
    while (n>0) {
        currfreq[n%10]++;
        n /= 10;
    }
    int ret = 1;
    for (int i = 0; i<10; i++)
        if (currfreq[i] > 1) {
            ret = 0;
            break;
        }
    return ret;
}

void getAllParts(int arr[10], int numPartsLeft, int leftover, int idx) {
    if (numPartsLeft == 1) {
        if (!nums[10-leftover]) return;
        long v = 0;
        for (int i = 10-leftover; i<10; i++) {
            v *= 10;
            v += nums[i];
        }
        currNumbers[idx++] = v;
        if (!checkDuplicates(v*currmult)) {
            restore(v*currmult);
            return;
        }
        for (int i = 0; i<10; i++) if (!currfreq[i]) return;
        //found a valid config
        //now to find max we sort the products in lexographic descending order.
        //for eg. if products are 27,3,8596410; they are sorted 8596410,3,27 to produce
        //8596410327, the largest concatenation possible. Then convert this to int and compare with max.
        // for (int i = 0; i<idx; i++) {
        //     printf("%ld ", currNumbers[i]);
        // }
        // printf("\n");
        char products[10][10] = {{0}};
        for (int i = 1; i<idx; i++) sprintf(products[i], "%ld",currNumbers[0]*currNumbers[i]);
        qsort(products, idx, sizeof(char)*10, cmp);
        long value = 0;

        for (int i = 0; i<idx-1; i++) {
            long val;
            sscanf(products[i], "%ld", &val);
            long tmp = 0;
            while (val > 0) {
                tmp *= 10;
                tmp += val%10;
                val /= 10;
            }
            while (tmp > 0) {
                value *= 10;
                value += tmp % 10;
                tmp /= 10;
            }
        }
        if (value > ans) ans = value;
        return;
    }
    if (!idx) {
        for (int i = 0; i<10; i++) {
            currfreq[i] = 0;
            currNumbers[i] = 0;
        }
        currmult = 0;
        for (int i = 1; i<leftover; i++) {
            currmult *= 10;
            currmult += nums[i-1];
            if (currmult%3) continue;
            currNumbers[idx] = currmult;
            arr[idx] = i;
            //printf("init: %ld\n", currmult);
            getAllParts(arr,numPartsLeft - 1,leftover-i,idx+1);
        }
        return;
    }
    if (!nums[10-leftover]) return;
    long val = 0;
    for (int i = 1; i<leftover; i++) {
        //here itself do conversion, multiplication and check for repeat digits.
        val *= 10;
        val += nums[9-leftover+i];
        if (idx>1 && val > currNumbers[idx-1]) return;
        //prune if duplicates are found
        if (!checkDuplicates(currmult*val)) {
            restore(currmult*val);
            continue;
        }
        arr[idx] = i;
        currNumbers[idx] = val;
        getAllParts(arr,numPartsLeft - 1,leftover-i,idx+1);
        restore(currmult*val);
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
        if (!a[0]) return;
        for (int size = 3; size<=10; size++) {
            int arr[size];
            getAllParts(arr,size,10,0);
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
    //first we generate all permutations of 0...10 
    //then partition it into pieces so that first piece is divisible by 3
    //this has to be the case if we want this number to multiply with all other pieces and when 
    //concatenated give pandigital 0-9. (pandigital 0-9 is divisible by 9)
    //this optimization reduces runtime by around 45%.
    //Now just run a dfs and prune when the frequency of any digit in any of the multiplications is
    //more than 1
    permute(nums,0,9);
    printf("%ld\n", ans);
    return 0;
}