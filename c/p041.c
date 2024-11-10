//https://projecteuler.net/problem=41
//Pandigital Prime

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n <= 3) {
        return 1;
    }
    for (int i = 2; i<sqrt((float) n)+1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    // an 8 or 9-digit pandigital prime cannot exist, as sum of digits is
    // divisible by 3, so all permutations of the first 9 natural numbers
    // will also be divisible by 3
    //brute-force solution
    int end_digits[3] = {1,3,7};
    int n = 0;
    int p = 1;
    for (int i = 7; i>0; i--) {
    for (int j = 7; j>0; j--) {
    for (int k = 7; k>0; k--) {
    for (int l = 7; l>0; l--) {
    for (int m = 7; m>0; m--) {
    for (int n = 7; n>0; n--) {
    for (int o = 0; o<3; o++) {
        int d = end_digits[o];
        if (i == j || i == k || i == l || i == m || i == n || i == d || j == k
         || j == l || j == m || j == n || j == d || k == l || k == m || k == n
         || k == d || l == m || l == n || l == d || m == n || m == d || n == d
            ) {
                continue;
            }
        int s = d+10*n+100*m+1000*l+10000*k+100000*j+1000000*i;
        if (isPrime(s) == 1) {
            printf("%d\n",s);
            return 0;
        }
    }}}}}}}
}