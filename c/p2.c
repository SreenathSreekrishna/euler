//https://projecteuler.net/problem=2
//Even Fibonacci numbers

#include <stdio.h>

int main(void) {
    int n = 4000000;
    int sum = 0;
    int curr = 2;
    int prev = 1;
    while (curr <= n) {
        if (curr % 2 == 0) {
            sum += curr;
        }
        int s = curr + prev;
        prev = curr;
        curr = s;
    }
    printf("%d\n", sum);
}