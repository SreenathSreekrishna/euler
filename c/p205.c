//https://projecteuler.net/problem=205
//Dice Game

#include <stdio.h>

int main(void) {
    int distrp[37] = {0};
    int distrc[37] = {0};
    for (int i = 0; i<262144; i++) {
        int n = i;
        int s = 0;
        for (int j = 0; j<9; j++) {
            s += n%4+1;
            n /= 4;
        }
        distrp[s]++;
    }
    for (int i = 0; i<46656; i++) {
        int n = i;
        int s = 0;
        for (int j = 0; j<6; j++) {
            s += n%6+1;
            n /= 6;
        }
        distrc[s]++;
    }
    double ans = 0;
    for (int i = 0; i<=36; i++) {
        for (int j = 0; j<i; j++) {
            ans += (double) distrp[i]/262144 * (double) distrc[j]/46656;
        }
    }
    printf("%.7f\n", ans);
    return 0;
}