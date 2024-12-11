//https://projecteuler.net/problem=93
//Arithmetic Expressions

#include <stdio.h>

double operate(double a, double b, int op) {
    if (op == 0) {
        return a+b;
    }
    if (op == 1) {
        return a-b;
    }
    if (op == 2) {
        return a*b;
    }
    if (op == 3) {
        if (b == 0) return 0;
        return ((double) a)/(double) b;
    }
    return 0;
}

int maxConsecutive(int vals[4]) {
    int expressible[100000] = {0};
    int arr[24][4] = {
        {vals[0],vals[1],vals[2],vals[3]},
        {vals[0],vals[1],vals[3],vals[2]},
        {vals[0],vals[2],vals[1],vals[3]},
        {vals[0],vals[2],vals[3],vals[1]},
        {vals[0],vals[3],vals[1],vals[2]},
        {vals[0],vals[3],vals[2],vals[1]},
        {vals[1],vals[0],vals[2],vals[3]},
        {vals[1],vals[0],vals[3],vals[2]},
        {vals[1],vals[2],vals[0],vals[3]},
        {vals[1],vals[2],vals[3],vals[0]},
        {vals[1],vals[3],vals[0],vals[2]},
        {vals[1],vals[3],vals[2],vals[0]},
        {vals[2],vals[0],vals[1],vals[3]},
        {vals[2],vals[0],vals[3],vals[1]},
        {vals[2],vals[1],vals[0],vals[3]},
        {vals[2],vals[1],vals[3],vals[0]},
        {vals[2],vals[3],vals[0],vals[1]},
        {vals[2],vals[3],vals[1],vals[0]},
        {vals[3],vals[0],vals[1],vals[2]},
        {vals[3],vals[0],vals[2],vals[1]},
        {vals[3],vals[1],vals[0],vals[2]},
        {vals[3],vals[1],vals[2],vals[0]},
        {vals[3],vals[2],vals[0],vals[1]},
        {vals[3],vals[2],vals[1],vals[0]},
    };

    for (int i = 0; i<24; i++) {
        for (int op1 = 0; op1<4; op1++) {
            for (int op2 = 0; op2<4; op2++) {
                for (int op3 = 0; op3<4; op3++) {
                    double results[2] = {0};
                    results[0] = operate(operate(arr[i][0],arr[i][1],op1),operate(arr[i][2],arr[i][3],op2),op3);
                    results[1] = operate(operate(operate(arr[i][0],arr[i][1],op1),arr[i][2],op2),arr[i][3],op3);
                    for (int k = 0; k<2; k++) {
                        if (results[k] > 0 && results[k] - (int) results[k] == 0) {
                            expressible[(int)results[k]]++;
                        }
                    }
                }
            }
        }
    }

    int i = 1;
    while (expressible[i]) {
        i++;
    }
    return i-1;
}

int main(void) {
    int max = -1;
    int v[4];
    for (int a = 1; a<10; a++) {
        for (int b = a+1; b<10; b++) {
            for (int c = b+1; c<10; c++) {
                for (int d = c+1; d<10; d++) {
                    int vals[] = {a,b,c,d};
                    int m = maxConsecutive(vals);
                    if (m > max) {
                        v[0] = a; v[1] = b; v[2] = c; v[3] = d;
                        max = m;
                    }
                }
            }
        }
    }
    printf("%d%d%d%d\n", v[0],v[1],v[2],v[3]);

    return 0;
}