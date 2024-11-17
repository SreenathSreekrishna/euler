//https://projecteuler.net/problem=79
//Passcode Derivation

#include <stdio.h>
#define N 100

int numbers[N] = {0};
int numSize = 0;

void insert(int i, int v) {
    int tmp = numbers[i];
    for (int j = i+1; j<numSize; j++) {
        int tmp1 = numbers[j];
        numbers[j] = tmp;
        tmp = tmp1;
    }
    numbers[i] = v;
    numSize++;
}

void delete(int i) {
    for (int j = i; j<numSize;j++) {
        numbers[j] = numbers[j+1];
    }
    numSize--;
}

int main(void) {
    FILE *f = fopen("../files/0079_keylog.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!");
        return 1;
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    int nums[50];
    for (int i = 0; i<50; i++) {
        fscanf(f,"%d\n",&nums[i]);
    }

    int rules[100][2];
    for (int i = 0; i<50; i++) {
        int a = nums[i]/100;
        int b = (nums[i]/10)%10;
        int c = nums[i]%10;
        int exists1 = 0;
        int exists2 = 0;
        rules[2*i][0] = a;
        rules[2*i][1] = b;
        rules[2*i+1][0] = b;
        rules[2*i+1][1] = c;
    }
    numSize = 0;
    for (int i = 0; i<100; i++) {
        int aloc = -1;
        int bloc = -1;
        for (int k = 0; k<numSize; k++) {
            if (numbers[k] == rules[i][0]) {
                aloc = k;
            }
            if (numbers[k] == rules[i][1]) {
                bloc = k;
            }
        }
        if (aloc < 0 && bloc < 0) {
            insert(numSize,rules[i][0]);
            insert(numSize,rules[i][1]);
            continue;
        }
        if (aloc < 0) {
            insert(bloc, rules[i][0]);
            continue;
        }
        if (bloc < 0) {
            insert(aloc+1, rules[i][1]);
            continue;
        }
        if (aloc < bloc) {
            continue;
        }
        if (aloc > bloc) {
            insert(bloc,rules[i][0]);
        }
    }
    int used[10] = {0};
    for (int i = 0; i<numSize; i++) {
        if (!used[numbers[i]]) {
            printf("%d",numbers[i]);
        }
        used[numbers[i]] = 1;
    }
    printf("\n");
    return 0;
}
