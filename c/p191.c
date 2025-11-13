//https://projecteuler.net/problem=191
//Prize Strings

#include <stdio.h>
#define N 30

int main(void) {
    //let f(n) be the number of ways to have n days with no lates and no 3 consecutive absences.
    //notice that this is just a linear recurrence. f(n) = f(n-1) + f(n-2) + f(n-3).
    //as there are only 0 or 1 lates, we can split the problem into 2 cases.
    //case 1: no lates -> f(n)
    //case 2: exactly 1 late -> 
    //assume the late day is in position k, then the first k-1 days must have no lates and no 3 absences, and the 
    //last n-k days must have no lates and no 3 absences, so the total number of ways becomes sum of f(k-1)*f(n-k) for k=1 to n.
    //we just add this to f(n) to get the answer.

    long f[N+1] = {0};
    f[0] = 1; f[1] = 2; f[2] = 4;
    for (int i = 3; i<=N; i++) f[i] = f[i-1] + f[i-2] + f[i-3];
    long ans = f[N];
    for (int k = 1; k<=N; k++) ans += f[k-1]*f[N-k];
    printf("%ld\n", ans);
    return 0;
}