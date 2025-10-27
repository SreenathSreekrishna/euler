//https://projecteuler.net/problem=174
//Hollow Square Laminae II

#include <stdio.h>

int main(void) {
    int ways[11] = {0};
    for (int i = 4; i<=1000000; i+=4) {
        int n = 0;
        for (int f = 2; f*f < i; f+=2) {
            if (i%f) continue;
            if (i/f % 2) continue;
            n++;
        }
        if (n<=10) ways[n]++;
    }
    int ans = 0;
    for (int i = 1; i<=10; i++) ans += ways[i];
    printf("%d\n", ans);
    return 0;
}