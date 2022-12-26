//https://projecteuler.net/problem=7
//10001st prime

#include <stdio.h>
#include <math.h>

int main(void) {
    int n = 10001;
    long num = 2;
    while (n) {
        int isPrime = 1;
        for (int i = 2; i<=sqrt(num); i++) {
            if (num % i == 0) {
                isPrime = 0;
                break;
            }
        }
        num+=1;
        if (isPrime) {
            if (n % 1000000 == 0) {
                printf("%d\n", n);
            }
            n -= 1;
        }
    }
    printf("%li\n", num-1);
    return 0;
}