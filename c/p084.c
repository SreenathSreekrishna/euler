//https://projecteuler.net/problem=84
//Monopoly Odds

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int chance(int pos, int *ch_id) {
    int c = *(ch_id);
    *ch_id = (c + 1) % 16;
    if (c == 0) return 0;
    if (c == 1) return 10;
    if (c == 2) return 11;
    if (c == 3) return 24;
    if (c == 4) return 39;
    if (c == 5) return 5;
    if (c == 6 || c == 7) return (((pos + 10) % 40) / 10) * 10 + 5;
    if (c == 8) return (pos < 12 || pos > 28) ? 12 : 28;
    if (c == 9) return (pos + 37) % 40;
    return pos;
}

int community(int pos, int *cc_id) {
    int c = *(cc_id);
    *cc_id = (c + 1) % 16;
    if (c == 0) return 10;
    if (c == 1) return 0;
    return pos;
}

int main(void) {
    srand((unsigned int)time(NULL)); // Proper seeding for randomness

    int cc_id = rand() % 16;
    int ch_id = rand() % 16;

    int dist[40] = {0};
    int lastThree[3] = {0};
    int pos = 0;

    for (int i = 0; i < 100000000; i++) {
        int roll1 = rand() % 4 + 1;
        int roll2 = rand() % 4 + 1;
        int roll = roll1 + roll2;

        if (roll1 == roll2) {
            lastThree[0] = lastThree[1];
            lastThree[1] = lastThree[2];
            lastThree[2] = 1;
        } else {
            lastThree[0] = lastThree[1];
            lastThree[1] = lastThree[2];
            lastThree[2] = 0;
        }

        pos = (pos + roll) % 40;

        if (pos == 2 || pos == 17 || pos == 33) {
            pos = community(pos, &cc_id);
        }
        if (pos == 7 || pos == 22 || pos == 36) {
            pos = chance(pos, &ch_id);
        }
        if (pos == 30 || (lastThree[0] && lastThree[1] && lastThree[2])) {
            pos = 10;
        }
        dist[pos]++;
    }

    int maxes[3];

    for (int i = 0; i < 3; i++) {
        int max = -1, max_i = -1;
        for (int j = 0; j < 40; j++) {
            if (dist[j] > max) {
                max = dist[j];
                max_i = j;
            }
        }
        maxes[i] = max_i;
        dist[max_i] = -1;
    }
    
    for (int i = 0; i < 3; i++) {
        printf("%d",maxes[i]);
    }
    printf("\n");

    return 0;
}
