//https://projecteuler.net/problem=219
//Skew-cost Coding

#include <stdio.h>
#define N 1e9

int main(void) {
    //I noticed by computing the first few costs 5,11,18,26,35,44,54,64,74,85,96... two main things
    //1) we can compute the value of cost for n>2 along with the minimal set by just taking the minimal
    //   set for n-1, taking the element of the set with least cost and then in place of that, placing two
    //   strings with 0 and 1 appended to the end of the minimal string. for example, the minimal set for
    //   n=5 is 0000,0001,001,01,1; and for n=6 it is 0000,0001,001,01,10,11. we could also replace 0000 as
    //   it also has the same cost of 4 but we would obtain another set for n=6 with the same minimal cost.
    //2) i also noticed that the first order differences 5,6,7,8,9,9,10,10,11,11... of the cost function seem
    //   to follow a pattern. they are just consecutive integers starting with 5, with the number of times
    //   a number is repeated being given by the fibonacci-like recurrence a[n] = a[n-1]+a[n-4], for n>=5 and
    //   a5=1,a6=1,a7=1,a8=1. cost(n) is just the sum of the first n-1 first order differences.
    long a[1000] = {0,0,0,0,0,1,1,1,1};
    int k = 9;
    long sum = 4;
    while (sum < N-1) {
        a[k] = a[k-1]+a[k-4];
        sum += a[k++];
    }
    long ans = 0;
    for (int i = 5; i<k-1; i++) ans += i*a[i];
    ans += (k-1)*(N - sum + a[k-1] - 1);
    printf("%ld\n", ans);
    return 0;
}