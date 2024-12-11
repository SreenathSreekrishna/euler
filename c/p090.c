//https://projecteuler.net/problem=90
//Cube Digit Pairs

#include <stdio.h>

int canRepresent(int d1[6], int d2[6], int x, int y) {
    int hasX = 0, hasY = 0;
    for (int i = 0; i < 6; i++) {
        if (d1[i] == x || (x == 6 && d1[i] == 9) || (x == 9 && d1[i] == 6)) hasX = 1;
        if (d2[i] == y || (y == 6 && d2[i] == 9) || (y == 9 && d2[i] == 6)) hasY = 1;
        if (hasX && hasY) return 1;
    }
    hasX = 0; hasY = 0;
    for (int i = 0; i < 6; i++) {
        if (d2[i] == x || (x == 6 && d2[i] == 9) || (x == 9 && d2[i] == 6)) hasX = 1;
        if (d1[i] == y || (y == 6 && d1[i] == 9) || (y == 9 && d1[i] == 6)) hasY = 1;
        if (hasX && hasY) return 1;
    }

    return 0;
}

int checkCubes(int d1[6], int d2[6]) {
    int squares[][2] = {{0, 1}, {0, 4}, {0, 9}, {1, 6}, {2, 5}, {3, 6}, {4, 9}, {6, 4}, {8, 1}};
    for (int i = 0; i < 9; i++) {
        if (!canRepresent(d1, d2, squares[i][0], squares[i][1])) return 0;
    }
    return 1;
}

int main(void) {
    int t = 0;
    for (int a1 = 0; a1<5; a1++) {
    for (int a2 = a1+1; a2<10; a2++) {
    for (int a3 = a2+1; a3<10; a3++) {
    for (int a4 = a3+1; a4<10; a4++) {
    for (int a5 = a4+1; a5<10; a5++) {
    for (int a6 = a5+1; a6<10; a6++) {
    for (int b1 = 0; b1<5; b1++) {
    for (int b2 = b1+1; b2<10; b2++) {
    for (int b3 = b2+1; b3<10; b3++) {
    for (int b4 = b3+1; b4<10; b4++) {
    for (int b5 = b4+1; b5<10; b5++) {
    for (int b6 = b5+1; b6<10; b6++) {
        int arr1[] = {a1,a2,a3,a4,a5,a6};
        int arr2[] = {b1,b2,b3,b4,b5,b6};
        t += (checkCubes(arr1,arr2));
    }}}}}}}}}}}}
    printf("%d\n", t/2);
    return 0;
}