//https://projecteuler.net/problem=247
//Squares Under a Hyperbola

#include <stdio.h>
#include <math.h>

typedef struct hole {
    double a;
    double b;
    int idx1;
    int idx2;
    double side;
} hole;

hole holes[1000000];
int numHoles = 0;

void swapHole(int i, int j) {
    hole t = holes[i];
    holes[i] = holes[j];
    holes[j] = t;
}

static void heapifyUp(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (holes[p].side >= holes[i].side) break;
        swapHole(p, i);
        i = p;
    }
}

static void heapifyDown(int i) {
    while (1) {
        int l = 2*i + 1;
        int r = l + 1;
        int max = i;
        if (l < numHoles && holes[l].side > holes[max].side) max = l;
        if (r < numHoles && holes[r].side > holes[max].side) max = r;
        if (max == i) break;
        swapHole(i, max);
        i = max;
    }
}

void insert(hole h) {
    holes[numHoles] = h;
    heapifyUp(numHoles);
    numHoles++;
}

hole getmax(void) {
    hole top = holes[0];
    numHoles--;
    if (numHoles > 0) {
        holes[0] = holes[numHoles];
        heapifyDown(0);
    }
    return top;
}

double sidelen(hole h) {
    return (sqrt((h.a - h.b) * (h.a - h.b) + 4.0) - (h.a + h.b)) / 2.0;
}

int main(void) {
    hole init = {1.0, 0.0, 0, 0, (sqrt(5.0) - 1.0) / 2.0};
    insert(init);

    int ans = 0;
    int cnt = 1;

    while (cnt > 0) {
        ans++;
        hole curr = getmax();
        hole up = curr;
        up.b += curr.side; up.idx2++; up.side = sidelen(up);
        hole right = curr;
        right.a += curr.side; right.idx1++; right.side = sidelen(right);
        insert(up);
        insert(right);

        if (up.idx1 <= 3 && up.idx2 <= 3) cnt++;
        if (right.idx1 <= 3 && right.idx2 <= 3) cnt++;
        if (curr.idx1 <= 3 && curr.idx2 <= 3) cnt--;
    }

    printf("%d\n", ans);
    return 0;
}
