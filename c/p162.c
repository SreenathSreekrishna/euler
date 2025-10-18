//https://projecteuler.net/problem=162
//Hexadecimal Numbers

#include <stdio.h>

int main(void) {
    //if an n-digit hexadecimal contains all of {0,1,A}, then number of such numbers is - 
    //A: set of numbers missing 0 = 15^n
    //B: set of numbers missing 1 = 14*15^(n-1)
    //C: set of numbers missing A = 14*15^(n-1)
    //A ∩ B = 14^n
    //B ∩ C = 13*14^(n-1)
    //C ∩ A = 14^n
    //A ∩ B ∩ C = 13^n
    //N(n) = 15*16^(n-1) - 43*15^(n-1) + 41*14^(n-1) - 13^n
    unsigned long long s = 0;
    for (int n = 3; n<=16; n++) {
        long long sixteen = 15;
        long long fifteen = 43;
        long long fourteen = 41;
        long long thirteen = 13;
        for (int j = 0; j<(n-1); j++) {
            sixteen *= 16;
            fifteen *= 15;
            fourteen *= 14;
            thirteen *= 13;
        }
        s += (sixteen - fifteen + fourteen - thirteen);
    }
    char key[16] = "0123456789ABCDEF";
    char ans[17] = {0};
    int anslen = 0;
    while (s > 0) {
        ans[15 - anslen++] = key[s % 16];
        s /= 16;
    }
    printf("%s\n", ans);
    return 0;
}