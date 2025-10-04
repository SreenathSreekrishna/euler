//https://projecteuler.net/problem=147
//Rectangles in Cross-hatched Grids

#include <stdio.h>
#define A 43
#define B 47

long num(int a, int b) {
    //1 -> 0,1,2,3,4,5,6,7...
    //2 -> 9,19,29,39,49,59,69 ...
    //3 -> 51,86,
    //4 -> 166,250, ...
    //Through experimentation I found that for every fixed a,  n(a,b) with b>=a is an arithmetic progression
    //Then, I found the difference of this A.P. is just the sum of the first 'a' odd squares.
    //For n(a,a) I found a sequence in the oeis and a relating paper https://arxiv.org/pdf/2007.13472
    //So n(a,a) is a(a-1)(4a^2+4a+3)/6 (from the paper)
    //d(a) = 1^2 + 3^2 + 5^2 ... (2a-1)^2 = a(2a-1)(2a+1)/3
    if (a>b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    long d = a*(2*a-1)*(2*a+1)/3;
    long n = a*(a-1)*(4*a*a+4*a+3)/6;
    n += d*(b-a);
    n += a*b*(a+1)*(b+1)/4;
    return n;
}

int main(void) {
    long s = 0;
    for (int a = 1; a<=A; a++) for (int b = 1; b<=B; b++) s += num(a,b);
    printf("%ld\n", s);
    return 0;
}