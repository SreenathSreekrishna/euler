//https://projecteuler.net/problem=17
//Number letter counts

#include <stdio.h>

int getLetters(int num) {
    int ones[10] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4};
    int tens[10] = {0, 3, 6, 6, 5, 5, 5, 7, 6, 6};
    int teens[10] = {3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
    int letters = 0;
    //get number of thousands
    int thousands = num / 1000;
    //get the three least significant digits
    int lsd = num % 1000;
    int hundredsPlace = lsd / 100;
    int tensPlace = (lsd - hundredsPlace * 100) / 10;
    int onesPlace = lsd % 10;
    if (tensPlace == 1) {
        //adding the letters for numbers ending with teens
        letters += teens[onesPlace];
    }
    else {
        //adding the letters for twenty/thirty/forty in numbers like forty-one
        letters += tens[tensPlace];
        //adding the letters for one in numbers like forty-one
        letters += ones[onesPlace];
    }
    if (hundredsPlace > 0) {
        //adding the letters for one/two/three in numbers like three hundred
        letters += ones[hundredsPlace];
        //adding the letters for "hundred" in numbers like three hundred
        letters += 7;
    }
    if ((onesPlace!=0 || tensPlace!=0) && (hundredsPlace!=0 || thousands!=0)) {
        //adding the letters for the word "and" in numbers like three hundred and five
        letters += 3;
    }
    if (thousands > 0) {
        //adding the letters for the word "thousand"
        letters += 8;
    }
    else {
        return letters;
    }
    return letters + getLetters(thousands);
}

int main(void) {
    int n = 1000;
    int letters = 0;
    for (int i = 1; i<=n; i++) {
        letters += getLetters(i);
    }
    printf("%d\n", letters);
    return 0;
}