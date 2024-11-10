//https://projecteuler.net/problem=31
//Coin Sums

#include <stdio.h>
#define ncoins 8
#define amount 200

int main(void) {
    int coins[ncoins] = {1,2,5,10,20,50,100,200};
    int lookup[ncoins+1][amount+1];
    for (int i = 1; i<amount+1; i++) {
        lookup[0][i] = 0;
    }
    for (int i = 0; i<ncoins+1; i++) {
        lookup[i][0] = 1;
    }
    for (int i = 1; i<ncoins+1; i++) {
        for (int j = 1; j<amount+1; j++) {
            int k = j - coins[i-1];
            int s;
            if (k < 0) {
                s = 0;
            }
            else {
                s = lookup[i][k];
            }
            lookup[i][j] = lookup[i-1][j] + s;
        }
    }
    printf("%d\n", lookup[ncoins][amount]);
    return 0;
}