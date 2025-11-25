//https://projecteuler.net/problem=209
//Circular Logic

#include <stdio.h>

int main(void) {
    //Let T(a,b,c,d,e,f) be the transformation (a,b,c,d,e,f) -> (b,c,d,e,f,a^b&c)
    //We precompute all values of T for all 64 (a,b,c,d,e,f) first.
    //Now, the problem is reduced to finding # of tau such that tau(i) & tau(T[i]) = 0 for all i.
    //now, we compute all cycles within T[i]. this is because the possibilities for a number in a cycle
    //only depend on the other numbers in the same cycle, not in other cycles. thus, we compute the number
    //of possibilities for each cycle in T[i] and then find their product for the answer.
    //The number of possibilities for a cycle depends solely on the cycle alone. This is because the condition
    //tau(i) & tau(T[i]) = 0 is equivalent to counting the number of binary circles of length the same
    //as the cycle length such that there are no two adjacent 1s. This can be computed using combinatorics
    //and recurrence. this comes out to just the nth number in the lucas recurrence, (1,3,4,7...); which is 
    //like fibonacci but starts with 2,1 instead of 0,1.
    int T[64] = {0};
    for (int i = 0; i<64; i++) {
        int n = i;
        int bin[6]; //f,e,d,c,b,a
        for (int j = 0; j<6; j++) {
            bin[j] = n%2;
            n/=2;
        }
        for (int j = 4; j>=0; j--) {
            T[i] += bin[j];
            T[i] *= 2;
        }
        T[i] += bin[5]^(bin[4]&bin[3]);
    }
    long L[64] = {2,1};
    for (int i = 2; i<64; i++) L[i] = L[i-1]+L[i-2];

    int visited[64] = {0};
    long ans = 1;
    for (int i = 0; i<64; i++) {
        if (visited[i]) continue;
        int curr = i;
        int len = 0;
        do {
            visited[curr] = 1;
            curr = T[curr];
            len++;
        }
        while (curr != i);
        ans *= L[len];
    }
    printf("%ld\n", ans);
    return 0;
}