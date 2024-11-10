//https://projecteuler.net/problem=4
//Largest palindrome product

#include <stdio.h>

int isPalindrome (int num) {
    //returns 1 if yes 0 if no
    if (num / 100000 != num % 10) {
        return 0;
    }
    if ((num / 10000) % 10 != (num % 100) / 10) {
        return 0;
    }
    if ((num / 1000) % 100 != (num % 1000) / 100) {
        return 0;
    }

    return 1;
}

int main(void) {
    for (int i = 999; i>100; i--) {
        for (int j = 999; j>100; j--) {
            int mult = i*j;
            if (isPalindrome(mult)) {
                printf("%d\n", mult);
                return 0;
            }
        }
    }
}