//https://projecteuler.net/problem=188
//Hyperexponentiation

#include <stdio.h>

long long modpow(long long a, long long d, long long n) {
    long long res = 1, base = a % n;
    while (d > 0) {
        if (d % 2) res = (res * base) % n;
        base = (base * base) % n;
        d /= 2;
    }
    return (long long)res;
}

int main(void) {
    //using euler's theorem (extension of fermats theorem), we can see that when we consider a^e mod m,
    //it is equivalent to a^(e mod phi(m)) mod m.
    //Thus, 1777 ^^ 1855 ... mod 10^8 is just 1777^(1777 ^^ 1854 mod 4*10^7) mod 10^8
    // = 1777^(1777^(1777 ^^ 1853 mod 16*10^6) mod 4*10^7) mod 10^8 
    //the moduli are thus 10^8, 4*10^7, 16*10^6, 64*10^5, 256*10^4, 1024*10^3, 4096*10^2, 16384*10,
    //65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1 in order.
    //when the modulus is 2, it is just 1 no matter what the tetration is. thus we can just reverse engineer
    //from that point on.
    long ans = 1;
    long modulus = 2;
    while (modulus < 65536) {
        ans = modpow(1777, ans, modulus);
        modulus *= 2;
    }
    while (modulus <= 100000000) {
        ans = modpow(1777, ans, modulus);
        modulus /= 2;
        modulus *= 5;
    }
    printf("%ld\n", ans);
    return 0;
}