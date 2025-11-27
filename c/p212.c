//https://projecteuler.net/problem=212
//Combined Volume of Cuboids

#include <stdio.h>
#define N 50000

typedef struct {
    int x,y,z;
} Point;

typedef struct {
    Point p1,p2;
} Cuboid;

Cuboid cuboids[N];
long long ans = 0;

int invalid(Cuboid c){
    return (c.p2.x <= c.p1.x || c.p2.y <= c.p1.y || c.p2.z <= c.p1.z);
}

long long volume(Cuboid c){
    return (long long) (c.p2.x-c.p1.x) * (c.p2.y-c.p1.y) * (c.p2.z-c.p1.z);
}

Cuboid intersection(Cuboid a, Cuboid b){
    Cuboid r;
    r.p1.x = (a.p1.x > b.p1.x) ? a.p1.x : b.p1.x;
    r.p1.y = (a.p1.y > b.p1.y) ? a.p1.y : b.p1.y;
    r.p1.z = (a.p1.z > b.p1.z) ? a.p1.z : b.p1.z;
    r.p2.x = (a.p2.x < b.p2.x) ? a.p2.x : b.p2.x;
    r.p2.y = (a.p2.y < b.p2.y) ? a.p2.y : b.p2.y;
    r.p2.z = (a.p2.z < b.p2.z) ? a.p2.z : b.p2.z;
    return r;
}

void dfs(Cuboid curr, int start, int parity){
    for(int i = start; i < N; i++){
        Cuboid nxt = intersection(curr, cuboids[i]);
        if (invalid(nxt)) continue;
        long long v = volume(nxt);
        ans += v*parity;
        dfs(nxt, i+1, -parity);
    }
}

int main(void){
    int S[6*N];
    for(int k=1;k<=55;k++){
        long long val = (100003LL - 200003LL*k + 300007LL*k*k*k) % 1000000LL;
        if(val < 0) val += 1000000LL;
        S[k-1] = (int) val;
    }
    for (int k = 55; k<6*N; k++) S[k] = (S[k-24] + S[k-55]) % 1000000;
    for (int i = 0; i<N; i++) {
        int x0 = S[6*i]%10000; int y0 = S[6*i+1]%10000; int z0 = S[6*i+2]%10000;
        cuboids[i].p1 = (Point) {x0,y0,z0};
        cuboids[i].p2 = (Point) {x0+(S[6*i+3]%399)+1, y0+(S[6*i+4]%399)+1, z0+(S[6*i+5]%399)+1};
    }

    for(int i = 0; i < N; i++){
        long long v = volume(cuboids[i]);
        ans += v;
        dfs(cuboids[i], i + 1, -1);
    }

    printf("%lld\n", ans);
    return 0;
}