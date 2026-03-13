//https://projecteuler.net/problem=259
//Reachable Numbers

#include <stdio.h>

unsigned int reachable[1000000];
long big[100000];
int biglen = 0;

typedef struct fraction {
    long p;
    long q;
} fraction;

long gcd(long a, long b) {
    long tmp;
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

fraction reduce(fraction f) {
    if (f.q < 0) { f.p = -f.p; f.q = -f.q; }
    long g = gcd(f.p, f.q);
    if (g == 0) return f;
    return (fraction) {f.p/g, f.q/g};
}

long getReachableSum(fraction nums[], int numslen) {
    long ret = 0;
    if (numslen == 1) {
        if (nums[0].q == 1 && nums[0].p > 0) {
            long v = nums[0].p;
            if (v < 32000000) {
                int idx = v / 32;
                int bit = v % 32;
                if (((reachable[idx] >> bit) & 1U)) return 0;
                reachable[idx] |= (1U << bit);
            } else {
                for (int k = 0; k < biglen; k++) if (big[k] == v) return 0;
                big[biglen++] = v;
            }
            return nums[0].p;
        }
        return 0;
    }
    fraction newArr[9];
    for (int i = 0; i<numslen-1; i++) {
        fraction a = nums[i];
        fraction b = nums[i+1];
        for (int j = 0; j<numslen; j++) {
            if (j < i) newArr[j] = nums[j];
            else if (j > i+1) newArr[j-1] = nums[j];
        }
        newArr[i] = reduce((fraction) {a.p*b.q + a.q*b.p, a.q*b.q});
        ret += getReachableSum(newArr, numslen-1);
        newArr[i] = reduce((fraction) {a.p*b.q - a.q*b.p, a.q*b.q});
        ret += getReachableSum(newArr, numslen-1);
        newArr[i] = reduce((fraction) {a.p*b.p, a.q*b.q});
        ret += getReachableSum(newArr, numslen-1);
        newArr[i] = reduce((fraction) {a.p*b.q, a.q*b.p});
        ret += getReachableSum(newArr, numslen-1);
    }
    return ret;
}

long getAnswer(int arr[], int start, int len) {
    if (start == 10) {
        fraction nums[9];
        for (int i = 0; i<len; i++) nums[i] = (fraction) {arr[i], 1};
        long ret = getReachableSum(nums, len);
        return ret;
    }
    long ret = 0;
    int curr = 0;
    for (int i = start; i<=9; i++) {
        curr *= 10;
        curr += i;
        arr[len] = curr;
        ret += getAnswer(arr, i+1, len+1);
    }
    return ret;
}

int main(void) {
    int arr[9] = {0};
    printf("%ld\n", getAnswer(arr, 1, 0));
    return 0;
}