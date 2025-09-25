//https://projecteuler.net/problem=136
//Singleton Difference

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    //we can prove that the all such values of n are either - 
    //1) p = 3 mod 4
    //2) 4p where p=1 or p>=3
    //3) 16p where p=1 or p>=3
    int num = 2; //4 and 16
    int limit = 50000000;
    unsigned char *IS_PRIME = malloc(sizeof(unsigned char) * limit);
    for (int p = 2; p<limit; p++) {
        if (!IS_PRIME[p]) {
            for (int j = 2; p * j<limit; j++)
                IS_PRIME[p * j]= 1;
            if (p == 2) continue;
            if (p % 4 == 3) num++;
            if (16*p < limit) num++;
            if (4*p < limit) num++;
        }
    }
    printf("%d\n", num);
    free(IS_PRIME);
    return 0;
}