//https://projecteuler.net/problem=38
//Pandigital Multiples

#include <stdio.h>
#include <stdlib.h>

int pandigital(int n, int m) {
    //tests if n * (1,2,3, ..., m) when concatenated contains digits 1-9 pandigital
    int arr[10] = {0,0,0,0,0,0,0,0,0,0};
    int num = 0;
    long s = 0;
    for (int k = 1; k<=m; k++) {
        char *thing = malloc(5 * sizeof(char));
        sprintf(thing, "%d", n*k);
        int i = 0;
        while (thing[i] != '\0') {
            arr[thing[i]-48]++;
            int pow = 1;
            for (int l = 0; l<(8-s); l++) {
                pow *= 10;
            }
            num += ((thing[i]-48) * pow);
            i++;
            s++;
            
        }
        free(thing);
    }
    if (arr[0] != 0) {
        return 0;
    }
    for (int i = 1; i<10; i++) {
        if (arr[i] != 1) {
            return 0;
        }
    }
    return num;
}

int main(void) {
    int max = 0;
    for (int j = 0; j<10; j++) {
        for (int i = 0; i<=10000; i++) {
            int n = pandigital(i, j);
            if (n > max) {
                max = n;
            }
        }
    }
    printf("%d\n",max);
    return 0;
}