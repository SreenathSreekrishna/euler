//https://projecteuler.net/problem=223
//Almost Right-angled Triangles I

#include <stdio.h>
#include <math.h>
#define N 25000000

typedef struct Node {
    int a;
    int b;
    int c;
} Node;

Node frontier[N];
int frontierLen = 2;

int main(void) {
    //i tried a lot of number theory methods to solve using prime factorization but none of them worked well.
    //instead i found this wiki page https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples
    //about primitive pythagorean triples being generated using a ternary tree and just matrix mult.
    //as this is based on a vieta-jumping kind of proof and there are no extra non-constant terms
    //in our modified pythagorean equation a^2+b^2 = c^2+1, the same matrices work. we only need to
    //modify the initial node. for this equation specifically, it turns out that there are two root
    //nodes, namely (1,1,1) and (1,2,2). using these all other solutions can be obtained using dfs.
    //i found out that recursion is not possible due to the call stack overflow so i just use a while loop.
    //the three matrices in the wiki that give the children to (a,b,c) when multiplied are
    //A = 1 -2 2  B = 1 2 2  C = -1 2 2
    //    2 -1 2      2 1 2      -2 1 2
    //    2 -2 3      2 2 3      -2 2 3
    long ans = 0;
    frontier[0] = (Node) {1,2,2};
    frontier[1] = (Node) {1,1,1};
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