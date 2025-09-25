//https://projecteuler.net/problem=135
//Same Differences

#include <stdio.h>
#include <math.h>

int main(void) {
    //(a+k)^2 - a^2 - (a-k)^2 = n
    //a(4k-a)=n (notice that n=0 or 3 mod 4)
    //a>k => 3a^2 > n => n/a<sqrt(3n)
    //for n=27 -> (9,3) (27,7)
    int num = 0;
    for (int n = 1155; n<1000000; n++) {
        if (n%4 == 1 || n%4 == 2) continue;
        int c = 0;
        for (int i = 1; i<sqrt(3*n); i++)
            if (n%i == 0 && (i%4 == 0) == ((n/i)%4 == 0)) c++;
        if (c == 10) num++;
    }
    printf("%d\n", num);
    return 0;
}