//https://projecteuler.net/problem=56
//Powerful Digit Sum

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int max = -1;
    for (int a = 1; a<100; a++) {
        for (int b = 1; b<100; b++) {
            int *n = malloc(sizeof(int) * 256);
            for (int i = 0; i<256; i++) {
                n[i] = 0;
            }
            n[0] = 1;
            for (int k = 0; k<b; k++) {
                int *m = malloc(sizeof(int) * 256);
                for (int i= 0; i< 256; i++) {
                    m[i] = 0;
                }
                for (int i = 0; i<253; i++) {
                    int v = m[i] + n[i]*a;
                    m[i] = v % 10;
                    int t =(m[i+1] + (v / 10) % 10);
                    m[i+1] = t % 10;
                    t = (m[i+2] + v/100 + (t - t%10)/10);
                    m[i+2] = t % 10;
                    m[i+3] += (t - t%10) / 10;
                }
                free(n);
                n = m;
            }
            int s = 0;
            for (int i = 0; i<256; i++) {
                s+=n[i];
            }

            if (s > max) {
                max = s;
            }

            free(n);
        }
    }

    printf("%d\n", max);
    return 0;
}