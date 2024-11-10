//https://projecteuler.net/problem=57
//Square Root Convergents

#include <stdio.h>

int numDigits(int num[]) {
    int d;
    for (int i = 0; i<500; i++) {
        if (num[i]) {
            d = i;
        }
    }
    return d;
}

int main(void) {
    //the convergents to sqrt(2) satisfy the following recurrence relation - 
    //if p/q is a convergent, the next one will be (p+2q)/(p+q)
    int count = 0;
    int n[500] = {0};
    int d[500] = {0};
    n[0] = 3;
    d[0] = 2;
    for (int i = 0; i<1000; i++) {
        int n_[500] = {0};
        int d_[500] = {0};

        for (int j = 0; j<499; j++) {
            int x = n_[j] + n[j] + 2*d[j];
            int y = d_[j] + n[j] + d[j];
            n_[j] = x % 10;
            n_[j+1] += (x - n_[j]) / 10;
            d_[j] = y % 10;
            d_[j+1] += (y - d_[j]) / 10;
        }

        for (int j = 0; j<500; j++) {
            n[j] = n_[j];
            d[j] = d_[j];
        }

        int nD = numDigits(n);
        int dD = numDigits(d);
        
        count += (nD > dD);
    }

    printf("%d\n", count);
    return 0;
}