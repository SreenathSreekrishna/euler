//https://projecteuler.net/problem=39
//Integer Right Triangles

#include <stdio.h>

int main(void) {
    int max = 0;
    int maxNum = -1;
    for (int i = 3; i<=1000; i++) {
        int count = 0;
        for (int a = 1; a<(i-1); a++) {
            for (int b = 1; b<(i-a); b++) {
                int c = i - a - b;
                if (a*a + b*b == c*c) {
                    count++;
                }
            }
        }
        if (count > max) {
            max = count;
            maxNum = i;
        }
    }
    printf("%d\n", maxNum);
    return 0;
}