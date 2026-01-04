//https://projecteuler.net/problem=242
//Odd Triplets

#include <stdio.h>
#define N 1000000000000

long f(long n) {
    if (n < 2) return n;
    if (n%2 == 0) return 3*f(n/2);
    return 2*f(n/2)+f(n/2+1);
}

int main(void) {
    //number of k-element subsets of {1,2,3,...n} with odd sum can be calculated as follows
    //we are assuming odd n and k for the purposes of the problem. in this case, {1,2,3...n}
    //contains (n-1)/2 even numbers and (n+1)/2 odd numbers. for the sum to be odd, the no.
    //of odd elements in the subset must be odd. thus the total count is just - 
    //sum from i=1 to k over odd i of ((n+1)/2 choose i) * ((n-1)/2 choose (k-i)).
    //using generating functions and the binomial theorem, a closed form of this sum can be
    //calculated. this is given below.
    //f(n,k) = (nCk - ((n-1)/2)C((k-1)/2) * (-1)^((k+1)/2))/2
    //for each n <= 1e12 we need to find the number of 1<=k<=n with k odd such that this
    //closed form is odd.
    //to find out the parity of f(n,k) we have to find out when 2f(n,k) is 2 mod 4.
    //As f(n,k) is always an integer, 2f(n,k) is 0 or 2 mod 4. to find out when it is 2, we
    //just need to discard the cases where nCk = ((n-1)/2)C((k-1)/2) * (-1)^((k+1)/2) mod 4.
    //this is equivalent to nCk = ((n-1)/2)C((k-1)/2) * (k-2) mod 4
    //thus we want to count # of (n,k) : nCk != ((n-1)/2)C((k-1)/2) * (k-2) mod 4
    //by getting counts for small k<n<=N, i noticed that the count C(N) was equivalent to the
    //number of k<n<N/4 such that nCk is odd.
    //this can be solved by counting numbers without carries in binary (like how i used base 7)
    //for p148. i used an O(n) method in p148 but was able to find an O(logn) method in the 
    //p148 thread that will be required for this problem.
    printf("%ld\n", f(N/4));
    return 0;
}