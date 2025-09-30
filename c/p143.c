//https://projecteuler.net/problem=143
//Torricelli Triangles

#include <stdio.h>
#include <stdlib.h>

int m = 147695;
int deg[120000];
int *adj[120000];
int order[120000];
int rankv[120000];
int fdeg[120000];
int *fwd[120000];

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b,a%b);
}

int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}
int cmp_vertex(const void *a, const void *b) {
    int u = *(const int*)a;
    int v = *(const int*)b;
    if (deg[u] != deg[v]) return deg[u] - deg[v];
    return u - v;
}


int main() {
    //due to angles inscribed in a circle, it can be proven that angle ATB = angle BTC = angle CTA = 120 deg
    //Using the cosine rule, a^2 = q^2 + r^2 + qr, b^2 = p^2 + q^2 + pq, c^2 = r^2 + p^2 + rp
    int num = 0;
    int solutions[147695][2]; //ran this program once before to find num=147695
    for (int m = 1; m<=691; m++) {
        for (int n = 1; m*m-3*n*n-2*m*n>0; n++) {
            if ((m+n)%2) continue;
            int p = (m*m-3*n*n-2*m*n)/4;
            int q = m*n;
            if (p+q>=120000) continue;
            if (gcd(p,q)>2) continue;
            if (p>q) {
                int tmp = p;
                p = q;
                q = tmp;
        }
            for (int s = 1; s*(p+q)<120000; s++) {
                solutions[num][0] = s*p;
                solutions[num++][1] = s*q;
            }
        }
    }

    //now use the solutions to generate a graph and then find all triangles within that graph (3-cycles)
    //each 3-cycle corresponds to a single torricelli triangle

    int n = -1;
    for (int i = 0; i < m; i++) {
        int u = solutions[i][0];
        int v = solutions[i][1];
        if (u > n) n = u;
        if (v > n) n = v;
        deg[u]++; deg[v]++;
    }
    n++;

    for (int i = 0; i < n; i++) {
        adj[i] = malloc((deg[i] > 0 ? deg[i] : 1) * sizeof(int));
        deg[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int u = solutions[i][0];
        int v = solutions[i][1];
        adj[u][deg[u]++] = v;
        adj[v][deg[v]++] = u;
    }

    for (int u = 0; u < n; u++) {
        if (deg[u] == 0) continue;
        qsort(adj[u], deg[u], sizeof(int), cmp_int);
        int w = 0;
        for (int i = 0; i < deg[u]; i++) {
            int x = adj[u][i];
            if (x == u) continue;
            if (w == 0 || adj[u][w-1] != x)
                adj[u][w++] = x;
        }
        deg[u] = w;
    }

    for (int i = 0; i < n; i++) order[i] = i;
    qsort(order, n, sizeof(int), cmp_vertex);
    for (int i = 0; i < n; i++) rankv[order[i]] = i;

    for (int u = 0; u < n; u++) fdeg[u] = 0;
    for (int u = 0; u < n; u++) {
        for (int j = 0; j < deg[u]; j++) {
            int v = adj[u][j];
            if (rankv[u] < rankv[v]) fdeg[u]++;
        }
    }
    for (int u = 0; u < n; u++) {
        fwd[u] = malloc((fdeg[u] > 0 ? fdeg[u] : 1) * sizeof(int));
        fdeg[u] = 0;
    }
    for (int u = 0; u < n; u++) {
        for (int j = 0; j < deg[u]; j++) {
            int v = adj[u][j];
            if (rankv[u] < rankv[v]) fwd[u][fdeg[u]++] = v;
        }
        if (fdeg[u] > 1) qsort(fwd[u], fdeg[u], sizeof(int), cmp_int);
    }

    int sum = 0;
    int used[120000] = {0};
    for (int u = 0; u < n; u++) {
        for (int i = 0; i < fdeg[u]; i++) {
            int v = fwd[u][i];
            int p1 = 0, p2 = 0;
            while (p1 < fdeg[u] && p2 < fdeg[v]) {
                int a = fwd[u][p1];
                int b = fwd[v][p2];
                if (a == b) {
                    if (!used[u+v+a]) {
                        used[u+v+a] = 1;
                        sum += (u+v+a);
                    }
                    p1++; p2++;
                }
                else if (a < b) p1++;
                else p2++;
            }
        }
    }

    printf("%d\n", sum);

    for (int i = 0; i < n; i++) {
        free(adj[i]);
        free(fwd[i]);
    }

    return 0;
}
