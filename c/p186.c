// //https://projecteuler.net/problem=186
// //Connectedness of a Network

#include <stdio.h>

int parent[1000000];
int numConnected[1000000];

int findParent(int x){
    while(parent[x] != x){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void combine(int a, int b){
    int ra = findParent(a), rb = findParent(b);
    if(ra == rb) return;
    if(numConnected[ra] < numConnected[rb]){
        int t = ra; ra = rb; rb = t;
    }
    parent[rb] = ra;
    numConnected[ra] += numConnected[rb];
}

int main(void){
    for(int i=0;i<1000000;i++){
        parent[i] = i;
        numConnected[i] = 1;
    }

    int s[55];
    for(int k=1;k<=55;k++){
        long long val = (100003LL - 200003LL*k + 300007LL*k*k*k) % 1000000LL;
        if(val < 0) val += 1000000LL;
        s[(k-1) % 55] = (int)val;
    }

    long long curr = 1;
    long long ans = 0;

    while(numConnected[findParent(524287)] < 990000){
        int friends[2];
        for(int i=0; i<2; i++){
            long long k = curr;
            if(k > 55){
                int idx = (k-1) % 55;
                int a = s[(k-25) % 55];
                int b = s[(k-56) % 55];
                s[idx] = (a + b) % 1000000;
            }
            friends[i] = s[(k-1) % 55];
            curr++;
        }
        if(friends[0] != friends[1]) ans++;
        combine(friends[0], friends[1]);
    }
    printf("%lld\n", ans);

    return 0;
}
