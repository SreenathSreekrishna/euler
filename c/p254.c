//https://projecteuler.net/problem=254
//Sums of Digit Factorials

#include <stdio.h>
#define N 150

long facts[10] = {1,1,2,6,24,120,720,5040,40320,362880};

int checkSum(long n, int m) {
    //checks if sum of digits of n is m.
    while (n) {
        m -= n%10;
        n /= 10;
        if (m < 0) return 0;
    }
    return m == 0;
}

int compare(long a, long b) {
    int aarr[10] = {0};
    int barr[10] = {0};
    int adigits = 0, bdigits = 0;
    for (int i = 9; i>=0; i--) {
        aarr[i] = a/facts[i];
        adigits += aarr[i];
        barr[i] = b/facts[i];
        bdigits += barr[i];
        a %= facts[i];
        b %= facts[i];
    }
    if (adigits > bdigits) return -1;
    if (bdigits > adigits) return 1;
    for (int i = 1; i<=9; i++) {
        if (aarr[i] > barr[i]) {
            return 1;
        }
        if (aarr[i] < barr[i]) {
            return -1;
        }
    }
    return 0;
}

int main(void) {
    //minimum number of digits needed for n to have digit factorial sum = i.
    int minNeeded[362880] = {0};
    for (int i = 0; i<362880; i++) {
        int n = i;
        for (int j = 8; j>=0; j--) {
            minNeeded[i] += (n / facts[j]);
            n %= facts[j];
        }
    }
    //for k to be achieved by digit factorial sum, the smallest integer with the digit factorial sum
    //equal to k will just be an arrangement of k/9! 9s and minNeeded[k%9!] other digits.
    //if we want that integer to be smallest, the number of digits must be minimum,
    //k/9! + minNeeded[k%9!] must be minimum. because of the linear term, the numbers cant be too 
    //big. the max value of minNeeded is 36, so if m/9! + minNeeded[m%9!] < n/9! + minNeeded[n%9!],
    //then m/9! + 1 < n/9! + 36. This means m/9! - n/9! < 35, and thus (m-n) < 36*9!. this means the
    //gap between the optimal k and least possible k must be less than 36*9!. the least possible k is
    //just the number formed by taking (i/9) 9s and a leading (i%9). Then, we just iterate the next
    //36*9! numbers to find the one with valid digit sum and smaller valuation described above.
    //for example, to find g(20), the min is set as 299. We then iterate until 299+36*9! for another
    //better number that fits. the best one in this range coms out to be 5762. this is then converted
    //to base factorial and digit sum is taken to finally get sg(i).
    //noticed that after 63 the min solution is the optimal one for a huge optimization.
    long ans = 0;
    long limit = 36*facts[9];
    for (int i = 1; i<=N; i++) {
        long start = (i%9 + 1);
        for (int j = 0; j<i/9; j++) start *= 10;
        start--;
        long mink = start;
        long minVal = mink/facts[9] + minNeeded[mink%facts[9]];
        for (int j = 1; j<limit; j++) {
            if (i >= 63) break;
            long k = start+j;
            if (!checkSum(k,i)) continue;
            long value = k/facts[9] + minNeeded[k%facts[9]];
            if (value <= minVal && compare(k,mink) >= 0) {
                minVal = value;
                mink = k;
            }
        }
        long sg = 0;
        for (int j = 9; j>=0; j--) {
            long v = (mink / facts[j]);
            sg += j*v;
            mink %= facts[j];
        }
        ans += sg;
    }
    printf("%ld\n", ans);
    return 0;
}