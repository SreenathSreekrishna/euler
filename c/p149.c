//https://projecteuler.net/problem=149
//Maximum-sum Subsequence

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *s = malloc(sizeof(int) * 4000000);
    int count = 0;
    for (int i = 0; i<55; i++) {
        s[i] = (100003 - 200003*(i+1) + (long) 300007*(i+1)*(i+1)*(i+1))%1000000 - 500000;
    }
    for (int i = 55; i<4000000; i++) {
        s[i] = (s[i-24]+s[i-55]+1000000)%1000000 - 500000;
    }
    long max = 0;
    for (int i = 0; i<2000; i++) {
        long sumx[2001];
        long sumy[2001];
        sumx[0] = 0;
        sumy[0] = 0;
        for (int j = 0; j<2000; j++) {
            sumx[j+1] = sumx[j] + s[2000*i+j];
            sumy[j+1] = sumy[j] + s[2000*j+i];
        }
        for (int a = 0; a<2000; a++) {
            for (int b = a; b<2000; b++) {
                long v1 = sumx[b+1]-sumx[a];
                long v2 = sumy[b+1]-sumy[a];
                if (v1>max) max = v1;
                if (v2>max) max = v2;
            }
        }
    }
    for (int i = 0; i<2000; i++) {
        long *d1 = malloc(sizeof(long)*(i+2));
        long *d2 = malloc(sizeof(long)*(i+2));
        long *d3 = malloc(sizeof(long)*(i+2));
        long *d4 = malloc(sizeof(long)*(i+2));
        d1[0] = 0; d2[0] = 0; d3[0] = 0; d4[0] = 0;
        for (int j = 0; j<=i; j++) {
            int idx1 = 1999*j+i;
            int idx2 = 2001*j+1999-i;
            int idx3 = 2001*j+2000*(1999-i);
            int idx4 = 1999*j+2000*(1999-i)+1999;
            if (idx1 >= 4000000 || idx2 >= 4000000 || idx3 >= 4000000 || idx4 >= 4000000) {
                printf("%d\n", i);
            }
            d1[j+1] = d1[j] + s[idx1];
            d2[j+1] = d2[j] + s[idx2];
            d3[j+1] = d3[j] + s[idx3];
            d4[j+1] = d4[j] + s[idx4];
        }
        for (int a = 0; a<=i; a++) {
            for (int b = a; b<=i; b++) {
                long v1 = d1[b+1]-d1[a];
                long v2 = d2[b+1]-d2[a];
                long v3 = d3[b+1]-d3[a];
                long v4 = d4[b+1]-d4[a];
                if (v1>max) max=v1;
                if (v2>max) max=v2;
                if (v3>max) max=v3;
                if (v4>max) max=v4;
            }
        }
        free(d1); free(d2); free(d3); free(d4);
    }
    printf("%ld\n", max);
    free(s);
    return 0;
}