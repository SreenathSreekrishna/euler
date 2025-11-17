//https://projecteuler.net/problem=197
//A Recursively Defined Sequence

#include <stdio.h>
#include <math.h>

long g(long n) {
    return (long) pow(2,30.403243784-pow(((double) n / 1e9),2));
}

int main(void) {
    //let v_n = 10^9 * u_n
    //i noticed that u_n oscillates between two values, so i wrote a loop to stop when it repeats.
    //the two values oscillating will be the same as  u_n and u_(n+1), so i just output their sum.
    long v[4096] = {0};
    v[0] = -1;
    v[1] = g(-1e9);
    int len = 2;
    do {
        v[len] = g(v[len-1]);
        len++;
    } while (v[len-1] != v[len-3]);
    printf("%.9f\n", 1e-9 * (v[len-1]+v[len-2]));
    return 0;
}