//https://projecteuler.net/problem=251
//Cardano Triplets

#include <stdio.h>
#define N 110000000

long gcd(long a, long b) {
    long tmp;
    while (b) {
        tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

long extendedGCD(long a, long b, long *x, long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long x1, y1;
    long g = extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

long modInverse(long a, long m) {
    long x, y;
    long g = extendedGCD(a, m, &x, &y);
    if (g != 1) {
        return -1;
    }
    long res = (x % m + m) % m;
    return res;
}

int main(void) {
    //using cardano's method for solving a depressed cubic, we can reverse engineer how the
    //sum of cube roots was obtained. by doing so, i get the equation 27(b^2 * c - a^2) = (2a-1)^3
    //this implies 3|2a-1 => 2a = 1 mod 3 => a = 2 mod 3. thus a=3k-1 for positive integer k
    //by substituting and rearranging, we obtain the equation b^2 * c = k^2 * (8k-3)
    //let gcd(b,k) = d; b=dx, k=dy. in this case, x^2 * c = y^2 * (8dy - 3)
    //as gcd(x,y) = 1; 8dy-3 = tx^2 for a positive integer t.
    //=> d = (tx^2 + 3)/8y, c = ty^2 for a valid t.
    //thus the condition is now only the bounds and that 8y | (tx^2 + 3)
    //=> tx^2 = -3 mod 8y. 
    //as c<=N => ty^2 <= N => y^2 <= N => y <= sqrt(N)
    //k = dy = (tx^2 + 3)/8 >= (x^2 + 3)/8
    //=> 3k-1 = (3x^2 + 1)/8 = a
    //a <= N => (3x^2 + 1)/8 <= N => x <= sqrt((8N-1)/3)
    //we now have bounds to search x and y.
    int ans = 0;
    for (long y = 1; y*y <= N; y++) {
        long mod = 8*y;
        long v = (8*(N-y*y)-1) / 3;
        for (long x = 1; x*x <= v; x++) {
            if (gcd(x,y) > 1) continue;
            long g = gcd(x*x, mod);
            if (3 % g) continue;
            long xprime = x*x/g;
            long modprime = mod/g;
            long inv = modInverse(xprime, modprime)*(modprime-3/g);
            inv %= modprime;
            //if d>=1 tx^2 >= 8y-3 => t >= (8y-3)/x^2
            //thus we must find smallest t = inv mod modprime >= (8y-3)/x^2
            long tmin = (8*y-3)/(x*x);
            long t = (tmin + (modprime - (tmin - inv)%modprime))%modprime;
            //this is the min t. using the bounds and substitution i got the following eqn.
            //(x^3 + 8y^3 + 3x^2 y)t + (3x+y) <= 8yN
            long a = x*x*x+8*y*y*y+3*x*x*y;
            long b = 8*y*N - (3*x+y);
            //we want to now find the maximum m such that a(t+m*modprime) <= b
            //=> m <= (b - at)/(a*modprime)
            if (a*t > b) continue;
            ans += (b-a*t)/(a*modprime) + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}