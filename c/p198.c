//https://projecteuler.net/problem=198
//Ambiguous Numbers

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    //for a rational number to have two best approximations, the number must be equidistant from both
    //approximations. it is also possible to prove that the two best approximations must be farey neighbours
    //i.e. if they are p/q < r/s; ps-qr = 1. this can be done by contradiction and a few properties of 
    //farey sequences. if they are non-adjacent, their mediant ((p+r)/(q+s)) will be part of the sequence,
    //and will be closer to their average (x) than at least one of the two, making them not best approx.
    //as this is a contradiction, they must be adjacent terms of a farey sequence. ps-qr=1.
    //the problem now becomes finding all (ps+qr)/2qs for ps-qr=1 within the denominator bounds specified
    //in the problem. we explore the farey tree until the denominator becomes too big and then
    //backtrack. this gives us the number of possible solutions. we then offset because of the initial few
    //denominators that we skipped during initialization.

    long m = (long)floor(sqrt(5e7));
    long *arr = malloc(m * sizeof(long));

    int len = 0;
    for (long v = 100; v < m; v++) arr[len++] = v;

    long a = m;
    long ans = 5e7 - 50;

    while (len) {
        long b = arr[len - 1];
        if (a*b > 5e7) {
            len--;
            a = b;
        } else {
            ans++;
            arr[len++] = a+b;
        }
    }

    printf("%ld\n", ans);
    free(arr);
    return 0;
}