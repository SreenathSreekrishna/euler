//https://projecteuler.net/problem=161
//Triominoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//HASHMAP constants
#define INITIAL_SIZE 16384
#define LOAD_FACTOR 0.6

//PROBLEM constants
#define N 9
#define M 12

typedef struct gridE {
    unsigned long long mask1;
    unsigned long long mask2;
} gridE;

typedef struct {
    gridE key;
    long value;
    int used;
} HashEntry;

typedef struct {
    size_t size;
    size_t count;
    HashEntry *table;
} HashMap;

// --- Hash map core functions ---

static inline uint64_t hash_gridE(const gridE *g) {
    // mix mask1 and mask2 into a single 64-bit value via xors and shifts,
    // then do splitmix-style finalization.
    uint64_t x = g->mask1 ^ (g->mask2 + 0x9e3779b97f4a7c15ULL + (g->mask1<<6) + (g->mask2>>2));
    // splitmix64-like finalizer
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    x = x ^ (x >> 31);
    return x;
}

static inline int gridE_equal(const gridE *p, const gridE *q) {
    return p->mask1 == q->mask1 && p->mask2 == q->mask2;
}

HashMap *hashmap_create(void) {
    HashMap *h = malloc(sizeof(HashMap));
    h->size = INITIAL_SIZE;
    h->count = 0;
    h->table = calloc(h->size, sizeof(HashEntry));
    return h;
}

void hashmap_free(HashMap *h) {
    free(h->table);
    free(h);
}

static void hashmap_resize(HashMap *h);

void hashmap_put(HashMap *h, gridE key, long value) {
    if ((double)h->count / h->size > LOAD_FACTOR)
        hashmap_resize(h);

    uint64_t hash = hash_gridE(&key);
    size_t idx = hash % h->size;

    while (h->table[idx].used) {
        if (gridE_equal(&h->table[idx].key, &key)) {
            h->table[idx].value = value;
            return;
        }
        idx = (idx + 1) % h->size;
    }

    h->table[idx].used = 1;
    h->table[idx].key = key;
    h->table[idx].value = value;
    h->count++;
}

long *hashmap_get(HashMap *h, const gridE *key) {
    uint64_t hash = hash_gridE(key);
    size_t idx = hash % h->size;

    while (h->table[idx].used) {
        if (gridE_equal(&h->table[idx].key, key))
            return &h->table[idx].value;
        idx = (idx + 1) % h->size;
    }
    return NULL;
}

static void hashmap_resize(HashMap *h) {
    size_t old_size = h->size;
    HashEntry *old_table = h->table;

    h->size *= 2;
    h->count = 0;
    h->table = calloc(h->size, sizeof(HashEntry));

    for (size_t i = 0; i < old_size; i++) {
        if (old_table[i].used)
            hashmap_put(h, old_table[i].key, old_table[i].value);
    }
    free(old_table);
}

//--------------------------------------------------

HashMap *memo;

long getNumPossibilities(int grid[M][N], int iStart, int n) {
    gridE ge;
    int i, j;
    int exit = 0;
    for (i = iStart; i<M; i++) {
        for (j = 0; j<N; j++) {
            if (!grid[i][j]) {
                exit = 1;
                break;
            }
        }
        if (exit) break;
    }
    if (n == M*N/3) return 1;

    memset(&ge, 0, sizeof(ge));
    ge.mask1 = 0;
    ge.mask2 = 0;

    for (int r = 0; r < M; ++r) {
        for (int c = 0; c < N; ++c) {
            int idx = r * N + c;
            if (grid[r][c]) {
                if (idx < 64) ge.mask1 |= (1ULL << idx);
                else ge.mask2 |= (1ULL << (idx - 64));
            }
        }
    }

    long *val = hashmap_get(memo, &ge);
    if (val) {
        return (*val);
    }

    long s = 0;

    grid[i][j] = 1;
    //types of triominoes (6/7)
    if (i+1 < M && j+1 < N && !grid[i][j+1] && !grid[i+1][j]) {
        grid[i][j+1] = 1;
        grid[i+1][j] = 1;
        s += getNumPossibilities(grid,i,n+1);
        grid[i][j+1] = 0;
        grid[i+1][j] = 0;
    }
    if (i+1 < M && j+1 < N && !grid[i+1][j] && !grid[i+1][j+1]) {
        grid[i+1][j] = 1;
        grid[i+1][j+1] = 1;
        s += getNumPossibilities(grid,i,n+1);
        grid[i+1][j] = 0;
        grid[i+1][j+1] = 0;
    }
    if (i+1 < M && j+1 < N && !grid[i][j+1] && !grid[i+1][j+1]) {
        grid[i][j+1] = 1;
        grid[i+1][j+1] = 1;
        s += getNumPossibilities(grid,i,n+1);
        grid[i][j+1] = 0;
        grid[i+1][j+1] = 0;
    }
    if (i > 0 && j+1 < N && !grid[i][j+1] && !grid[i-1][j+1]) {
        grid[i][j+1] = 1;
        grid[i-1][j+1] = 1;
        s += getNumPossibilities(grid,i,n+1);
        grid[i][j+1] = 0;
        grid[i-1][j+1] = 0;
    }
    if (j > 0 && i+1 < M && !grid[i+1][j] && !grid[i+1][j-1]) {
        grid[i+1][j] = 1;
        grid[i+1][j-1] = 1;
        s += getNumPossibilities(grid,i,n+1);
        grid[i+1][j] = 0;
        grid[i+1][j-1] = 0;
    }
    if (i+2 < M && !grid[i+1][j] && !grid[i+2][j]) {
        grid[i+1][j] = 1;
        grid[i+2][j] = 1;
        s += getNumPossibilities(grid,i,n+1);
        grid[i+1][j] = 0;
        grid[i+2][j] = 0;
    }
    if (j+2 < N && !grid[i][j+1] && !grid[i][j+2]) {
        grid[i][j+1] = 1;
        grid[i][j+2] = 1;
        s += getNumPossibilities(grid,i,n+1);
        grid[i][j+1] = 0;
        grid[i][j+2] = 0;
    }
    hashmap_put(memo,ge,s);
    grid[i][j] = 0;
    return s;
}

int main(void) {
    memo = hashmap_create();
    int grid[M][N];
    memset(grid, 0, sizeof(grid));
    printf("%ld\n", getNumPossibilities(grid,0,0));
    hashmap_free(memo);
    return 0;
}