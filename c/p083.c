//https://projecteuler.net/problem=83
//Path Sum: Four Ways

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 80
#define INF INT_MAX

int matrix[N][N];
int dist[N][N];

typedef struct {
    int cost, x, y;
} Node;

typedef struct {
    Node *heap;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->heap = (Node *)malloc(capacity * sizeof(Node));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

void swapNodes(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *minHeap, int idx) {
    int parent = (idx - 1) / 2;
    while (idx > 0 && minHeap->heap[idx].cost < minHeap->heap[parent].cost) {
        swapNodes(&minHeap->heap[idx], &minHeap->heap[parent]);
        idx = parent;
        parent = (idx - 1) / 2;
    }
}

void heapifyDown(MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->heap[left].cost < minHeap->heap[smallest].cost)
        smallest = left;
    if (right < minHeap->size && minHeap->heap[right].cost < minHeap->heap[smallest].cost)
        smallest = right;
    if (smallest != idx) {
        swapNodes(&minHeap->heap[idx], &minHeap->heap[smallest]);
        heapifyDown(minHeap, smallest);
    }
}

void push(MinHeap *minHeap, int cost, int x, int y) {
    if (minHeap->size == minHeap->capacity) {
        return;
    }
    minHeap->heap[minHeap->size++] = (Node){cost, x, y};
    heapifyUp(minHeap, minHeap->size - 1);
}

Node pop(MinHeap *minHeap) {
    if (minHeap->size == 0) {
        return (Node){-1, -1, -1};
    }
    Node root = minHeap->heap[0];
    minHeap->heap[0] = minHeap->heap[--minHeap->size];
    heapifyDown(minHeap, 0);
    return root;
}

int dijkstra() {
    MinHeap *minHeap = createMinHeap(N * N);
    push(minHeap, matrix[0][0], 0, 0);
    dist[0][0] = matrix[0][0];

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    while (minHeap->size > 0) {
        Node current = pop(minHeap);
        int cost = current.cost, x = current.x, y = current.y;
        if (x == N - 1 && y == N - 1) {
            free(minHeap->heap);
            free(minHeap);
            return cost;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
                int new_cost = cost + matrix[nx][ny];
                if (new_cost < dist[nx][ny]) {
                    dist[nx][ny] = new_cost;
                    push(minHeap, new_cost, nx, ny);
                }
            }
        }
    }

    free(minHeap->heap);
    free(minHeap);
    return -1;
}

int main(void) {
    FILE *f = fopen("../files/p083_matrix.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(f, "%d,", &matrix[i][j]);
            dist[i][j] = INF;
        }
    }
    fclose(f);

    int result = dijkstra();
    printf("%d\n", result);
    return 0;
}
