//https://projecteuler.net/problem=244
//Sliders

#include <stdio.h>
#include <stdlib.h>
#define MAX 16384

typedef struct Puzzle {
    unsigned short grid;
    unsigned char holePos;
    long checkSum;
    int solutionLen;
} Puzzle;

Puzzle move(Puzzle puzzle, char mov) {
    int newgrid[16];
    for (int i = 0; i<16; i++) {
        newgrid[15 - i] = puzzle.grid % 2;
        puzzle.grid /= 2;
    }
    unsigned char newPos;
    if (mov == 'R') newPos = puzzle.holePos-1;
    else if (mov == 'L') newPos = puzzle.holePos+1;
    else if (mov == 'D') newPos = puzzle.holePos-4;
    else if (mov == 'U') newPos = puzzle.holePos+4;
    newgrid[puzzle.holePos] = newgrid[newPos];
    newgrid[newPos] = 0;
    unsigned short newGrid = 0;
    for (int i = 0; i<16; i++) {
        newGrid *= 2;
        newGrid += newgrid[i];
    }
    return (Puzzle) {newGrid, newPos, (puzzle.checkSum*243+mov)%100000007L, puzzle.solutionLen+1};
}

int main(void) {
    //RED -> 0, BLUE -> 1
    Puzzle *frontier = calloc(sizeof(Puzzle), MAX);
    int frontierStart = 0;
    int frontierLen = 1;
    unsigned char explored[65536][16] = {0};
    Puzzle initial = {0b0011001100110011, 0, 0, 0};
    Puzzle goal = {0b0101101001011010, 0, 0, 0};
    frontier[0] = initial;
    int minLen = 0;
    long ans = 0;
    while (frontierLen) {
        Puzzle curr = frontier[frontierStart];
        if (curr.holePos == goal.holePos && curr.grid == goal.grid) {
            if (!minLen) minLen = curr.solutionLen;
            if (curr.solutionLen == minLen) ans += curr.checkSum;
        }
        if (curr.holePos%4 != 3) {
            Puzzle next = move(curr, 'L');
            if (!explored[next.grid][next.holePos]) {
                frontier[(frontierStart+frontierLen++)%MAX] = next;
                explored[next.grid][next.holePos] = 1;
            }
        }
        if (curr.holePos%4) {
            Puzzle next = move(curr, 'R');
            if (!explored[next.grid][next.holePos]) {
                frontier[(frontierStart+frontierLen++)%MAX] = next;
                explored[next.grid][next.holePos] = 1;
            }
        }
        if (curr.holePos/4 != 3) {
            Puzzle next = move(curr, 'U');
            if (!explored[next.grid][next.holePos]) {
                frontier[(frontierStart+frontierLen++)%MAX] = next;
                explored[next.grid][next.holePos] = 1;
            }
        }
        if (curr.holePos/4) {
            Puzzle next = move(curr, 'D');
            if (!explored[next.grid][next.holePos]) {
                frontier[(frontierStart+frontierLen++)%MAX] = next;
                explored[next.grid][next.holePos] = 1;
            }
        }
        frontierStart++;
        frontierStart %= MAX;
        frontierLen--;
    }
    printf("%ld\n", ans);
    free(frontier);
    return 0;
}