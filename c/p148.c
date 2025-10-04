//https://projecteuler.net/problem=148
//Exploring Pascal's Triangle

#include <stdio.h>

int main(void) {
    //we want to find how many (n,r) with r<=n<10^9 such that n!/r!(n-r)! != 0 mod 7
    //=> v7(n!) = v7(r!) + v7((n-r)!)
    //It is a standard result that v_p(n!) = (n-s_p(n))/(p-1) where s_p(n) is just the sum of 
    //digits of n in base p.
    //Therefore, the problem becomes finding the number of ways to split n into a,b such that 
    //a+b = n and s7(a)+s7(b)=s7(n) where s7 is the sum of digits in base 7.
    //Notice that because of these two conditions, we cannot have carry in the sum a+b, as
    //that will cause the same result of n upon adding, but the sum of digits will decrease.
    //This can be calculated combinatorically for any n by just taking the digits of n
    //in base 7, adding 1 to each digit and then multiplying.
    //For example, to find the number of nondivisible r for n=100, we write n=202_7 and then
    //compute (2+1)(0+1)(2+1)=9 to find the number of possibilities for r.
    //We then add the number of possibilities over all n<10^9 to get the answer.
    long ans = 0;
    for (int i = 0; i<1000000000; i++) {
        int n = i;
        long prod = 1;
        while (n>0) {
            prod *= (long) (n%7+1);
            n /= 7;
        }
        ans += prod;
    }
    printf("%ld\n", ans);
    return 0;
}