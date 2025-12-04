//https://projecteuler.net/problem=221
//Alexandrian Integers

#include <stdio.h>
#include <stdlib.h>
#define N 150000

long nums[1000000];
long distinct[1000000];

int cmp(const void *a, const void *b) {
    if (*(long *)a > *(long *)b) return 1;
    if (*(long *)a < *(long *)b) return -1;
    return 0;
}

int main(void) {
    //if 1/A = 1/p + 1/q + 1/r and A = p*q*r
    //we can prove that q and r must always be negative, so we replace this equation with 1/A = 1/p-1/q-1/r
    //to work with only positive integers.
    // => 1/A = (qr-rp-pq)/pqr = (qr-rp-pq)/A
    // => qr-rp-pq = 1.
    //Thus the problem is now reduced to finding all triples (p,q,r) such that qr-rp-pq=1
    //(q-p)(r-p) = p^2 + 1
    //Thus, the alexandrian integers are precisely all the integers |pqr| where q=d+p, r=(p^2+1)/d+p where d
    //is a factor of p^2+1.
    int numLen = 0;
    for (long p = 1; p<=100000; p++) {
        long v = p*p+1;
        for (long d = 1; d*d <= v; d++) {
            if (v%d) continue;
            long q = d+p;
            long r = (v/d)+p;
            __int128_t n = (__int128_t) p*q*r;
            if (n>2e15 || n<0) continue;
            nums[numLen++] = p*q*r;
        }
    }
    qsort(nums,numLen,sizeof(long),cmp);
    distinct[0] = nums[0];
    int distinctLen = 1;
    for (int i = 1; i<numLen; i++) if (nums[i] != nums[i-1]) distinct[distinctLen++] = nums[i];
    printf("%ld\n", distinct[N-1]);
    return 0;
}