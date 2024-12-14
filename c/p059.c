//https://projecteuler.net/problem=59
//XOR Decryption

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    //we notice that the most occuring number in the cipher text is 80, 
    //which must be the space character; and as the 80 occurs on the third position;
    //80^c = 32; where abc is the key. this means c = 112, or 'p'
    char *buff;
    FILE *f = fopen("../files/p059_cipher.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!");
        return 1;
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    buff = malloc(len);
    fread(buff, 1, len, f);
    
    char data[2048];

    int num = 1;

    int p = 1;
    int n = 0;

    for (int i = len-1; i>=-1; i--) {
        if (buff[i] == ',' || i == -1) {
            data[num-1] = n;
            p = 1;
            n = 0;
            num++;
            continue;
        }
        n += (buff[i]-48)*p;
        p*=10;
    }

    for (int i = 0; i<(num / 2); i++) {
        int tmp = data[i];
        data[i] = data[num - i - 2];
        data[num - i - 2] = tmp;
    }

    // for (int i = 97; i<123; i++) {
    //     for (int j = 97; j<123; j++) {
    //         int invalid = 0;
    //         char d[num];
    //         int key[3] = {i,j,112};
    //         int spaceCount = 0;
    //         int validCharCount = 0;
    //         int numNums = 0;
    //         for (int l = 0; l<num; l++) {
    //             d[l] = data[l] ^ key[l % 3];
    //             if (d[l] < 32) {
    //                 invalid = 1;
    //                 break;
    //             }
    //             if (d[l] == 32) {
    //                 spaceCount++;
    //             }
    //             if ((d[l] > 96 && d[l] < 123) || (d[l] >= 48 && d[l]<58)) {
    //                 validCharCount++;
    //             }
    //             if ((d[l] >= 48 && d[l]<58)) {
    //                 numNums ++;
    //             }
    //         }
    //         d[num-1] = 0;
    //         if (invalid || spaceCount < 150 || validCharCount < 900 || numNums<20) {
    //             break;
    //         }
    //         printf("%s\n%c%c%c\n", d, key[0],key[1],key[2]);
    //     }
    // }
    // running the above code, we can find the key is 'exp'

    char d[num-1];
    int s = 0;
    char k[3] = "exp";

    for (int i = 0; i<num-1; i++) {
        d[i] = data[i] ^ k[i%3];
        s += d[i];
    }

    printf("%d\n",s);

    free(buff);
    return 0;
}