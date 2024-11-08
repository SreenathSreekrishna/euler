//https://projecteuler.net/problem=44
//Triangular, Pentagonal, and Hexagonal

#include <stdio.h>

int main(void) {
    //We can solve this by firstal generating hexagonal numbers and checking if they are pentagonal
    //We don't need to check if they are triangular as all hexagonal numbers are triangular
    //This means the numbers must satisfy n(3n-1)/2 = m(2m-1) for some integers m,n
    //Rearranging, we get 3(4m-1)^2 - (6n-1)^2 = 2. This is a pellian equation of the form 3x^2 - y^2 = 2
    //This can be solved using continued fractions; and we find (3,5) is the first (x,y) pair
    //Subsequent pairs can be generated using the relation (x_(n+1),y_(n+1)) = (2*x_n+y_n,3*x_n+2*y_n)
    //Now, we check if these (x,y) pairs have integers m,n such that 4m-1=x, 6n-1=y. This can be solved
    //using modular congruence as this means x is -1 mod 4, while y is -1 mod 6.

    int x = 571; //for (x,y) = (571,989); the number formed is 40755
    int y = 989;

    do {
        int x1 = 2*x + y;
        int y1 = 3*x + 2*y;
        x = x1;
        y = y1;
    } while (x % 4 != 3 || y % 6 != 5);

    int m = (x+1) / 4;
    int n = (y+1) / 6;

    printf("%li\n", (long) m*((long) 2*m-1));

    return 0;
}