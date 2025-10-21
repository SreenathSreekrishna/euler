//https://projecteuler.net/problem=166
//Criss Cross

#include <stdio.h>

int valid(int n) {
    return (n>=0 && n<10);
}

int main(void) {
    //Let the grid be 
    //A         B           C           S-A-B-C
    //D         E           F           S-D-E-F
    //G         H           I           S-G-H-I
    //S-A-D-G   S-B-E-H     S-C-F-I     A+B+C+D+E+F+G+H+I-2S
    //Other terms of the grid can be generated using only A...I
    //We can now solve for S using one of the diagonals (A+E+I+Bottom right = S)
    //This gives us S = (2A+B+C+D+2E+F+G+H+2I)/3
    //Now, all the conditions are satisfied except the last diagonal
    //Using the last diagonal, we can just solve for h, giving H = A+B+C-F-S+A+D+G.
    //Now, we simply check that all values are within bounds and count.
    int ans = 0;
    for (int A = 0; A<10; A++) {
    for (int B = 0; B<10; B++) {
    for (int C = 0; C<10; C++) {
    for (int D = 0; D<10; D++) {
    for (int E = 0; E<10; E++) {
    for (int F = 0; F<10; F++) {
    for (int G = 0; G<10; G++) {
    for (int I = 0; I<10; I++) {
        int v = (4*A+2*B+2*C+2*D+2*E+2*G+2*I);
        if (v % 4) continue;
        int S = v/4;
        int H = 2*A+B+C+D-F+G-S;
        if (!valid(S-A-B-C) || !valid(S-D-E-F) || !valid(S-G-H-I)
         || !valid(S-A-D-G) || !valid(S-B-E-H) || !valid(S-C-F-I)
         || !valid(A+B+C+D+E+F+G+H+I-2*S) || !valid(H)) continue;
        ans++;
    }}}}}}}}
    printf("%d\n", ans);
    return 0;
}