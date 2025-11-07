//https://projecteuler.net/problem=183
//Maximum Product of Parts

#include <stdio.h>
#include <math.h>
#define LIMIT 10000

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a%b);
}

int D(int N) {
    int k1 = (double) N / M_E;
    int k2 = k1+1;
    int k;
    if (log((double) N / k1)*k1 > log((double) N / k2)*k2) k=k1;
    else k = k2;
    k /= gcd(N,k); //reduce fraction to least terms
    while (k%2 == 0) k /= 2;
    while (k%5 == 0) k /= 5;
    if (k == 1) return -N;
    return N;
}

int main(void) {
    //for a given N, we want to find max of (N/k)^k over all positive integers k.
    //We can interpret this as a function of k, and differentiate in order to find the maximum.
    //Setting the differential to 0, we find this maximum at k=N/e.
    //As we want k to be a positive integer, and our function is continuous, we just have to check
    //the two integers on the sides of N/e and pick the one that produces the larger product.
    //if optimal k only contains 2s and 5s in its prime factorization, D(N)=-N, D(N)=N otherwise.
    int ans = 0;
    for (int N = 5; N<=LIMIT; N++) ans += D(N);
    printf("%d\n", ans);
    return 0;
}