//https://projecteuler.net/problem=128
//Hexagonal Tile Differences

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    for (int i = 2; i<sqrt(n)+1; i++) if (n % i == 0) return 0;
    return 1;
}

int main(void) {
    //for numbers which are not directly at 12:00 or 1:00, they cannot have three primes. this is because
    //they already have two consecutive numbers on either side and out of the remaining four, two can be
    //eliminated due to parity and divisibilty by 3. Thus, we only check the numbers at 12:00 and 1:00, also
    //checking only the required cases even in these numbers (only three of the six neighbours we need to check).
    int cnt = 2;
    int l = 1;
    long n = 0;
    while (cnt < 2000) {
        l++;
        if (isPrime(6*l-1) && isPrime(6*l+1) && isPrime(12*l+5)) {
            cnt++;
            n = (long) 3*l*(l-1)+2;
        }
        if (cnt >= 2000) break;
        if (isPrime(6*l-1) && isPrime(6*l+5) && isPrime(12*l-7)) {
            cnt++;
            n = (long) 3*l*(l+1)+1;
        }
    }
    printf("%li\n", n);
    return 0;
}