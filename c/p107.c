//https://projecteuler.net/problem=107
//Minimal Network

#include <stdio.h>

typedef struct Edge {
    int connects[2];
    int value;
} Edge;

void merge(Edge a[], int l, int m, int r) {
    int l1 = m - l + 1;
    int l2 = r - m;
    Edge left[l1], right[l2];
    
    for (int i = 0; i<l1; i++) left[i] = a[l+i];
    for (int i = 0; i<l2; i++) right[i] = a[m+i+1];
    
    int i = 0;
    int j = 0;
    int k = l;
    
    while (i<l1 && j<l2) {
        if (left[i].value <= right[j].value) {
            a[k] = left[i];
            i++;
        }
        else {
            a[k] = right[j];
            j++;
        }
        k++;
    }
    
    while (i < l1) {
        a[k] = left[i];
        i++;
        k++;
    }
    while (j < l2) {
        a[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(Edge a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int toInt(char s[], int len) {
    int p = 1;
    int t= 0;
    for (int i = len-1; i>=0; i--) {
        t += ((int) s[i]-48) * p;
        p *= 10;
    }
    return t;
}

int checkLoop(int m[40][40], Edge edge) {
    int n[40][40];
    for (int i = 0; i<40; i++) {
        for (int j = 0; j<40; j++) {
            n[i][j] = m[i][j];
        }
    }
    n[edge.connects[0]][edge.connects[1]] = n[edge.connects[1]][edge.connects[0]] = edge.value;
    int toVisit[1600];
    int toVisitLength = 1;
    toVisit[0] = edge.connects[0];
    int visited[40] = {0};
    int index = 0;
    while (index != toVisitLength) {
        int current = toVisit[index];
        visited[current]++;
        toVisit[toVisitLength] = -1;
        index++;
        for (int i = 0; i<40; i++) {
            if (!m[current][i]) continue;
            if (!visited[i]) {
                if (i == edge.connects[1]) return 1;
                toVisit[toVisitLength] = i;
                toVisitLength++;
            }
        }
    }
    return 0;
}

int main(void) {
    FILE *f = fopen("../files/p107_network.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
    Edge edges[1024];
    int sum = 0;
    int edgeCount = 0;
    for (int i = 0; i<40; i++) {
        Edge edge;
        for (int j = 0; j<i; j++) {
            char curr[16] = {0};
            int idx = 0;
            char c = fgetc(f);
            while (c!=',' && c!='\n') {
                if (c!='-') {
                    curr[idx] = c;
                    idx++;
                }
                c = fgetc(f);
            }
            if (idx == 0) continue;
            edge.value = toInt(curr,idx);
            edge.connects[0] = j;
            edge.connects[1] = i;
            edges[edgeCount++] = edge;
            sum += edge.value;
        }
        while (fgetc(f) != '\n') ;
    }
    
    mergeSort(edges, 0, edgeCount - 1);
    int matrix[40][40] = {{0}};
    
    int total = 0;
    for (int i = 0; i<edgeCount; i++) {
        if (!checkLoop(matrix,edges[i])) {
            matrix[edges[i].connects[0]][edges[i].connects[1]] = matrix[edges[i].connects[1]][edges[i].connects[0]] = edges[i].value;
            total += edges[i].value;
        }
    }
    
    printf("%d\n", sum-total);
    
    return 0;
}