//https://projecteuler.net/problem=240
//Top Dice

#include <stdio.h>

long long fac20 = 1;

long long numRolls(int topsum, int rolls[20], int idx) {
    if (idx > 20) return 0;
    if (idx == 20) {
        int freq[13] = {0};
        for (int i = 0; i<20; i++) freq[rolls[i]]++;
        int sum = 0;
        int numLeft = 10;
        for (int i = 12; i>=1; i--) {
            if (freq[i] >= numLeft) {
                sum += numLeft*i;
                break;
            }
            else sum += freq[i]*i;
            numLeft -= freq[i];
        }
        if (sum != topsum) return 0;
        long long num = fac20;
        for (int i = 1; i<=12; i++)
        for (int j = 1; j<=freq[i]; j++) num /= j;
        return num;
    }
    int start = idx == 0 ? 1 : rolls[idx-1];
    long long ret = 0;
    for (int i = start; i<=12; i++) {
        rolls[idx] = i;
        ret += numRolls(topsum, rolls, idx+1);
    }
    return ret;
}

int main(void) {
    for (int i = 1; i<=20; i++) fac20*=i;
    int rolls[20] = {0};
    printf("%lld\n", numRolls(70, rolls, 0));
    return 0;
}