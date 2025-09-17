//https://projecteuler.net/problem=109
//Darts

#include <stdio.h>

int d[22] = {1,18,4,13,6,10,15,2,17,3,19,7,16,8,11,14,9,12,5,20,25,0};

int main(void) {
    int s = 0;
    //last dart (always double)
    for (int i = 0; i<21; i++) {
    for (int j = 0; j<22; j++) {
    for (int k = 0; k<22; k++) {
    for (int a = 1; a<=3; a++) { //j multiplier
    for (int b = 1; b<=3; b++) { //k multiplier
        if (32*a + d[j] > 32*b + d[k]) continue;
        if ((j == 21 && a != 1) || (k == 21 && b != 1)) continue;
        if ((j == 20 && a == 3) || (k == 20 && b == 3)) continue;
        int v = 2*d[i]+a*d[j]+b*d[k];
        if (v<100) s++;
    }}}}}
    printf("%d\n",s);
    return 0;
}