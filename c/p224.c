//https://projecteuler.net/problem=223
//Almost Right-angled Triangles II

#include <stdio.h>
#include <math.h>
#define N 75000000

typedef struct Node {
    int a;
    int b;
    int c;
} Node;

Node frontier[N];
int frontierLen = 1;

int main(void) {
    //See p223 for explanation. this is literally the same but using a single root node (2,2,3)
    long ans = 0;
    frontier[0] = (Node) {2,2,3};
    while (frontierLen) {
        ans++;
        Node curr = frontier[frontierLen-1];
        int a = curr.a; int b = curr.b; int c = curr.c;
        frontierLen--;
        Node n1 = (Node) {a-2*b+2*c, 2*a-b+2*c, 2*a-2*b+3*c};
        Node n2 = (Node) {a+2*b+2*c, 2*a+b+2*c, 2*a+2*b+3*c};
        Node n3 = (Node) {-a+2*b+2*c, -2*a+b+2*c, -2*a+2*b+3*c};
        if (n1.a+n1.b+n1.c <= N) frontier[frontierLen++] = n1;
        if (n2.a+n2.b+n2.c <= N) frontier[frontierLen++] = n2;
        if (n3.a+n3.b+n3.c <= N && a!=b) frontier[frontierLen++] = n3;
        //if a=b then n1 and n3 are identical
    }
    printf("%ld\n", ans);
    return 0;
}