//https://projecteuler.net/problem=179
//Consecutive Positive Divisors

#include <stdio.h>
#define N 10000000

int numDivisors[N+1] = {0};

int main(void) {
    for (int i = 0; i<=N; i++) numDivisors[i]++;
    for (int i = 2; i<=N; i++)
        for (int j = i; j<=N; j+=i)
            numDivisors[j]++;
    int ans = 0;
    for (int i = 1; i<N; i++)
        ans += (numDivisors[i] == numDivisors[i+1]);
    
    printf("%d\n", ans);
    return 0;
}