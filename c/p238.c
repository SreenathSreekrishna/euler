//https://projecteuler.net/problem=238
//Infinite String Tour

#include <stdio.h>
#include <stdlib.h>
#define N 2000000000000000

long m = 20300713;

int main(void) {
    //i got confused because i thought that the problem would be possible to solve using a truly random
    //generator which seems to be impossible. however the way we solve is by exploiting the fact that the
    //pseudo-random generator is actually periodic, as when the original number s0 repeats, the following 
    //numbers are also identical as each next number is uniquely determined by the previous one.
    int *s = calloc(20000000, sizeof(int));
    int slen = 1;
    s[0] = 14025256;
    do {
        s[slen] = ((long) s[slen-1]*s[slen-1]) % m;
        slen++;
    } while (s[slen-1] != s[0]);
    slen--;
    unsigned char *string = calloc(8*slen, sizeof(unsigned char));
    int len = 0;
    for (int i = 0; i<slen; i++) {
        long a = s[i];
        int l = 0;
        while (a > 0) {
            l++;
            a /= 10;
        }
        a = s[i];
        int v = l;
        while (a>0) {
            v--;
            string[len+v] = a%10;
            a /= 10;
        }
        len += l;
    }
    long sum = 0;
    for (int i = 0; i<=len; i++) {
        if (i != len) sum += string[i];
    }
    int *p = calloc(sum, sizeof(int)); //p(i) for i < S (S is sum of non-repeating digits)
    sum = 0;
    for (int i = 0; i<=len; i++) {
        p[sum] = 1;
        if (i != len) sum += string[i];
    }
    for (int i = 1; i <= sum; i++)
    for (int j = 0, pos = 1; j + i <= 2*sum; j += string[(pos+len-1) % len], pos++) {
        if (p[(i+j) % sum] == 1) {
            p[i] = pos;
            break;
        }
    }
    long ans = 0;
    for (int i = 1; i <= sum; i++)
        ans += p[i];
    ans *= (N / sum);
    for (int i = 1; i <= N % sum; i++)
        ans += p[i];
    printf("%ld\n", ans);
    free(string);
    free(p);
    free(s);
    return 0;
}