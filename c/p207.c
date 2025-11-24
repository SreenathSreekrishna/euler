//https://projecteuler.net/problem=207
//Integer Partition Equations

#include <stdio.h>
#include <math.h>

int main(void) {
    //let 2^t = n. => k = n^2 - n = n(n-1) for an integer n. if it is a perfect partition, n is a power of 2
    //Let A(m) be number of partitions for k<=m, B(m) be no. of perfect ones.
    //We want to find least m with B(m)/A(m)<1/12345.
    //A(m) is just floor((1+sqrt(4k+1))/2) using quadratic formula.
    //B(m) is just floor(log_2(A(m))).
    //let x=(sqrt(4k+1)-1)/2. then we want to find least k such that floor(log_2(floor(x)+1))/floor(x) < 1/12345.
    //solving this inequality for k using calc, i get a lower bound of around 4400000000.
    long m = 44000000000;
    while (1) {
        long A = (sqrt(4*m+1) - 1.0F)/2.0F;
        long B = log2(A+1);
        if (A > 12345*B) break;
        m++;
    }
    printf("%ld\n", m);
    return 0;
}