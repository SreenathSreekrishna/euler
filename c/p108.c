//https://projecteuler.net/problem=108
//Diophantine Reciprocals I

#include <stdio.h>

int power(int p, int n) {
    int v = 1;
    for (int i = 0; i<n; i++) v *= p;
    return v;
}

int main(void) {
    //by solving this after factoring the equation we find that the number of solutions (x,y)
    //is just the number of factors of n^2 - 1 divided by 2. thus, the problem is reduced to just finding the
    //least possible value of n such that n^2 has greater than 2001 factors.
    int primes[] = {2,3,5,7,11,13,17,19};
    int min = __INT_MAX__;
    for (int i = 2001; i<=10000; i+=2) {
        int j = 2;
        int count = 0;
        int factors[16] = {0};
        int n = i;
        while (n>1) {
            while (n % j == 0) {
                n /= j;
                factors[count] = j;
                count++;
            }
            j++;
        }
        if (count <= 3) continue;
        int val = 1;
        for (int k = 0; k<count; k++) val *= power(primes[k], factors[count - k - 1] / 2);
        if (val < min && val>0) min = val;
    }
    printf("%d\n", min);
}