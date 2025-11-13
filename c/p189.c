//https://projecteuler.net/problem=189
//Tri-colouring a Triangular Grid

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 8

int main(void) {
    //the way i solved is by noticing that the number of colorings for side length N can be easily calculated
    //by just knowing the last row of the top N-1 rows (as adjacency is only dependent on that row).
    //the way my algorithm works is by generating all possibilities for the Nth row and then adding it based
    //on which bottom rows of the N-1 triangle will be valid when placing adjacent to it. then i just repeat
    //this starting at N=1 (which is just single triangle being colored in 3 ways) and work my way up to N=8
    //then i simply add the possibilities for all possible ending rows for the N=8 to get the total number
    //of colorings. this algorithm is only about O(4^n) in space and time, much better than the naive O(3^(n^2))

    //number of colorings with ending row encoded in trinary.
    long *numColorings = calloc(pow(3,N), sizeof(long));
    numColorings[0] = 1;
    numColorings[1] = 1;
    numColorings[2] = 1;
    //for n=1, the first topmost triangle can be one of 3 colors.
    long len;
    for (int i = 2; i<=N; i++) {
        len = pow(3,i);
        long *newColorings = calloc(len, sizeof(long));
        int *row = calloc(2*i-1, sizeof(int));
        for (int first = 0; first<3; first++) {
            row[0] = first;
            long l = pow(2,2*i-2);
            for (int j = 0; j<l; j++) {
                int rownum = first;
                int mask = j;
                for (int k = 1; k<2*i-1; k++) {
                    row[k] = (row[k-1]+2*(mask%2 + 1))%3;
                    if (k%2 == 0) {
                        rownum *= 3;
                        rownum += row[k];
                    }
                    mask /= 2;
                }

                //now just consider every odd indexed element of row as they are only touching the
                //previous row. find all possible touching last rows of the previous triangle using binary
                //and then convert that to trinary and add to total.

                long binl = pow(2, i-1);
                for (int k = 0; k<binl; k++) {
                    int prevrow = 0;
                    int m = k;
                    for (int v = 0; v<i-1; v++) {
                        prevrow *= 3;
                        prevrow += (row[2*v+1]+2*(m%2 + 1))%3;
                        m /= 2;
                    }
                    newColorings[rownum] += numColorings[prevrow];
                }
            }
        }
        for (int j = 0; j<len; j++) numColorings[j] = newColorings[j];
        free(row);
        free(newColorings);
    }

    long ans = 0;
    for (int i = 0; i<len; i++) ans += numColorings[i];
    printf("%ld\n", ans);
    free(numColorings);
    return 0;
}