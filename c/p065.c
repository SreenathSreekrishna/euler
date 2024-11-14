//https://projecteuler.net/problem=65
//Convergents of e

#include <stdio.h>
#define int_len 128

int sumDigits(int n[]) {
    int s = 0;
    for (int i = 0; i<int_len; i++) s+= n[i];
    return s;
}

int main(void) {
    int n = 99;
    int p[int_len] = {0};
    int q[int_len] = {0};
    p[0] = 1;
    q[0] = 1;
    for (int i = 0; i<n; i++) {
        int c = (n - i) / 3 * 2;
        int p1[int_len] = {0};
        int q1[int_len] = {0};
        if (i % 3 == n%3) {
            for (int j = 0; j<int_len - 2; j++) {
                p1[j] = q[j];
                int v = q1[j] + c*q[j]+p[j];
                q1[j] = v % 10;
                int x = q1[j+1]+(v-v%10)/10;
                q1[j+1] = x % 10;
                q1[j+2] = (x - x%10) / 10;
            }
        }
        else {
            for (int j = 0; j<int_len - 1; j++) {
                p1[j] = q[j];
                int v = q1[j] + p[j]+q[j];
                q1[j] = v % 10;
                q1[j+1] = q1[j+1]+(v-v%10)/10;
            }
        }
        for (int j = 0; j<int_len; j++) {
            p[j] = p1[j];
            q[j] = q1[j];
        }
    }

    int s[int_len] = {0};
    for (int i = 0; i<int_len; i++) {
        int v = s[i]+p[i]+q[i];
        s[i] = v % 10;
        s[i+1] += (v-v%10)/10;
    }

    printf("%d\n", sumDigits(s));
    return 0;
}