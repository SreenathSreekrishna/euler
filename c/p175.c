//https://projecteuler.net/problem=175
//Fractions and Sum of Powers of Two

#include <stdio.h>
#include <stdlib.h>

long gcd(long a, long b) {
    if (!b) return a;
    return gcd(b,a%b);
}

int main(void) {
    //f(n) is the number of modified binary representations of n. 
    //Notice that each digit of the modified binary is either contributing 0, 2^k or 2^(k+1)
    //to the total of n. Because of this, we can set up the generating function for f(n) by - 
    //product of (1 + x^(2^k) + x^(2^(k+1))) over sufficient values of k.
    //For example, to calculate f(10), we calculate the coefficient of x^10 in the expansion
    //This is just the coefficient of x^10 in (1+x+x^2)(1+x^2+x^4)(1+x^4+x^8)(1+x^8+x^16)
    //This gives the required value of 5.
    //After doing some research online, i found that this is also the generating function for something
    //called Stern's diatomic sequence. https://mathworld.wolfram.com/SternsDiatomicSeries.html
    //This sequence is related to something called a Calkin-Wilf Tree, which is just the ratio of
    //consecutive terms of the sequence, which is what we are looking for. Thus, the problem just becomes
    //finding the target rational number in a Calkin-Wilf binary Tree, and encoding the sequence of which
    //child (L or R / 0 or 1) of each node in the tree traces back to the root as a binary string.
    //This binary string when read gives the required n.
    //A Calkin-Wilf binary Tree is formed by starting with 1/1 and then adding (p+q)/q and p/(p+q) as
    //children to the rational number p/q in the tree. We just reverse this process starting with target
    //and ending with 1/1, noting which child the current rational number is (0 or 1) with respect to its
    //parent at each iteration.
    long p = 123456789;
    long q = 987654321;
    long g = gcd(p,q);
    p /= g; q /= g;
    int binlen = 1;
    unsigned char *binary = malloc(16777216*sizeof(unsigned char));
    binary[0] = 1;
    while (p != 1 || q != 1) {
        // 0 -> (p-q)/q
        // 1 -> p/(q-p)
        if (p > q) p = p-q;
        else q = q-p;
        binary[binlen++] = q>=p;
    }
    int count = 1;
    for (int i = binlen-1; i>0; i--) {
        if (binary[i] == binary[i-1]) count++;
        else {
            printf("%d,", count);
            count = 1;
        }
    }
    printf("%d\n", count);
    free(binary);
    return 0;
}