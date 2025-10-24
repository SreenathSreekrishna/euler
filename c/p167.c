//https://projecteuler.net/problem=167
//Investigating Ulam Sequences

#include <stdio.h>
#include <stdlib.h>
#define TESTLEN 3000000

int getPeriod(int vals[], int len, int start) {
    int period = (len - 1) - start;
    if (period < 2) return period;
    int *pi = (int*)malloc(sizeof(int) * period);
    if (!pi) return period;
    pi[0] = 0;
    for (int i = 1; i < period; ++i) {
        int j = pi[i - 1];
        while (j > 0 && vals[start + i] != vals[start + j]) {
            j = pi[j - 1];
        }
        if (vals[start + i] == vals[start + j]) ++j;
        pi[i] = j;
    }
    int p = period - pi[period - 1];
    if (p == 1) p = 2;
    if (p > period) p = period;
    free(pi);
    return p;
}


int main(void) {
    //https://mathworld.wolfram.com/UlamSequence.html
    //I found this article on ulam sequences from where I got this info
    //It has been proven that for odd v, U(2,v) will eventually have periodic differences
    //between consecutive terms. We should thus only compute the sequence until the cycles 
    //begin and then just find the phase of 10^11 mod the cyclicity to find the answer for
    //a particular v. sum this over all v given in the problem and we get the answer.
    //We can also optimize finding the differences upto the cyclicity by noticing that as only
    //2 even terms exist, and all others are odd, they must be sums of the even terms with some
    //other members of the sequence. Thus i initially calculate the even term then calculate the
    //next terms based on that.
    long long L = 1e11;
    long ans = 0;
    int *seq = malloc(sizeof(int)*TESTLEN);
    int *differences = malloc(sizeof(int) * TESTLEN);
    seq[0] = 2;
    for (int v = 5; v <= 21; v+=2) {
        seq[1] = v;
        int seqLen = 2;
        int curr = v+1;
        int l = 0;
        int r = 1;
        int num = 0;
        int even = 0;
        int idx = 0;
        while (seqLen < TESTLEN && !even) {
            while (seq[r] > curr/2) {
                while (seq[l] < curr - seq[r]) l++;
                if (seq[l] + seq[r] == curr) num++;
                if (num >= 2) {
                    r--;
                    l = 0;
                    break;
                }
                l = 0;
                r--;
                if (r<0) break;
            }
            if (num == 1) {
                seq[seqLen++] = curr;
                if (curr % 2 == 0) {
                    even = curr;
                    idx = seqLen;
                }
            }
            curr++;
            num = 0;
            r = seqLen-1;
        }
        num = 0;
        r = seqLen-1;
        while (seqLen < TESTLEN) {
            while (seq[r] > curr-2) r--;
            if (seq[r] == curr-2) num++;
            while (seq[r] > curr - even && r>=0) r--;
            if (seq[r] == curr-even) num++;
            if (num == 1) seq[seqLen++] = curr;
            curr+=2;
            num = 0;
            r = seqLen-1;
        }
        for (int i = 0; i<TESTLEN-1; i++) differences[i] = seq[i+1] - seq[i];
        int p = getPeriod(differences,seqLen,idx);
        long s1 = seq[(L-idx-1)%p+idx];
        for (int i = idx; i<idx+p; i++) {
            s1 += (long) differences[i]*((L-idx-1) / p);
        }
        ans += s1;
    }
    printf("%ld\n",ans);
    free(seq);
    free(differences);
    return 0;;
}
