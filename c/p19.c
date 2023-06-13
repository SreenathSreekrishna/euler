//https://projecteuler.net/problem=19
//Counting Sundays

#include <stdio.h>

int leapYear(int y) {
    if (y%4 != 0) {
        return 0;
    }
    if (y%100 == 0 && !(y%400 == 0)) {
        return 0;
    }
    return 1;
}

int main(void) {
    int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int sundays = 0;
    int days = 365; //one year after 1 jan 1900, which is given in the problem as a monday
    for (int i = 1901; i<2001; i++) {
        if (leapYear(i)) {
            months[1] = 29;
        }
        else {
            months[1] = 28;
        }
        for (int j = 0; j<12; j++) {
            if (days % 7 == 6) {
                sundays += 1;
            }
            days += months[j];
        }
    }
    printf("%d\n", sundays);
    return 0;
}