//https://projecteuler.net/problem=54
//Poker Hands

#include <stdio.h>
#include <stdlib.h>

typedef struct Card {
    int value; //2 ... 10 + J -> 11, Q -> 12, K -> 13, A -> 14
    int suit; // 1 -> Clubs, 2 -> Spades, 3 -> Hearts, 4 -> Diamonds
} Card;

Card createCard(char value, char suit) {
    Card c;

    if (value < 58  && value > 47) {
        c.value = value - 48;
    }
    else if (value == 'T') {
        c.value = 10;
    }
    else if (value == 'J') {
        c.value = 11;
    }
    else if (value == 'Q') {
        c.value = 12;
    }
    else if (value == 'K') {
        c.value = 13;
    }
    else if (value == 'A') {
        c.value = 14;
    }

    if (suit == 'C') {
        c.suit = 1;
    }
    else if (suit == 'S') {
        c.suit = 2;
    }
    else if (suit == 'H') {
        c.suit = 3;
    }
    else if (suit == 'D') {
        c.suit = 4;
    }
    return c;
}

int royalFlush(Card cards[5]) {
    int s = cards[0].suit;
    for (int i = 10; i<15; i++) {
        if (cards[i-10].value != i || cards[i-10].suit != s) {
            return 0;
        }
    }
    return 1;
}

int straight(Card cards[5]) {
    return (cards[1].value - cards[0].value == 1) &&
           (cards[2].value - cards[1].value == 1) &&
           (cards[3].value - cards[2].value == 1) &&
           (cards[4].value - cards[3].value == 1);
}

int suits(Card cards[5]) {
    return (cards[1].suit == cards[2].suit &&
            cards[3].suit == cards[4].suit &&
            cards[1].suit == cards[3].suit &&
            cards[0].suit == cards[1].suit);
}

int winner(Card hand1Unsorted[5], Card hand2Unsorted[5]) {
    //analyzes hands and checks returns 1 if hand 1 wins and 0 if it loses
    Card hand1[5] = {0};
    Card hand2[5] = {0};

    for (int i = 0; i<5; i++) {
        hand1[i] = hand1Unsorted[i];
        hand2[i] = hand2Unsorted[i];
    }

    for (int i = 0; i<5; i++) {
        for (int j = 0; j<4-i; j++) {
            if (hand1[j].value > hand1[j+1].value) {
                Card c = hand1[j+1];
                hand1[j+1] = hand1[j];
                hand1[j] = c;
            }

            if (hand2[j].value > hand2[j+1].value) {
                Card c = hand2[j+1];
                hand2[j+1] = hand2[j];
                hand2[j] = c;
            }
        }
    }

    int max1 = -1;
    int max2 = -1;

    int card1Freq[15] = {0};
    int card2Freq[15] = {0};

    for (int i = 0; i<5; i++) {
        if (hand1[i].value > max1) {
            max1 = hand1[i].value;
        }
        if (hand2[i].value > max2) {
            max2 = hand2[i].value;
        }
        card1Freq[hand1[i].value]++;
        card2Freq[hand2[i].value]++;
    }

    int freq1[6] = {0};
    int freq2[6] = {0};

    for (int i = 0; i<15; i++) {
        freq1[card1Freq[i]]++;
        freq2[card2Freq[i]]++;
    }

    //Royal flush -> 9, Straight flush -> 8
    //Four of a kind -> 7, Full house -> 6
    //Flush -> 5, Straight -> 4
    //Three of a kind -> 3, Two pairs -> 2
    //One pair -> 1

    int t1 = 0;
    int t2 = 0;

    if (royalFlush(hand1)) {
        t1 = 9;
    } else if (straight(hand1) && suits(hand1)) {
        t1 = 8;
    } else if (freq1[4] == 1) {
        t1 = 7;
    } else if (freq1[3] == 1 && freq1[2] == 1) {
        t1 = 6;
    } else if (suits(hand1)) {
        t1 = 5;
    } else if (straight(hand1)) {
        t1 = 4;
    } else if (freq1[3] == 1) {
        t1 = 3;
    } else if (freq1[2] == 2) {
        t1 = 2;
    } else if (freq1[2] == 1) {
        t1 = 1;
    }

    if (royalFlush(hand2)) {
        t2 = 9;
    } else if (straight(hand2) && suits(hand2)) {
        t2 = 8;
    } else if (freq2[4] == 1) {
        t2 = 7;
    } else if (freq2[3] == 1 && freq2[2] == 1) {
        t2 = 6;
    } else if (suits(hand2)) {
        t2 = 5;
    } else if (straight(hand2)) {
        t2 = 4;
    } else if (freq2[3] == 1) {
        t2 = 3;
    } else if (freq2[2] == 2) {
        t2 = 2;
    } else if (freq2[2] == 1) {
        t2 = 1;
    }

    if (t1 > t2) {
        return 1;
    } else if (t2 > t1) {
        return 0;
    }

    if (t1 == 1 || t1 == 3 || t1 == 7) {
        int c1,c2;
        for (int i = 0; i<15; i++) {
            if (card1Freq[i] >= 2) {
                c1 = i;
            }
            if (card2Freq[i] >= 2) {
                c2 = i;
            }
        }
        if (c1 > c2) {
            return 1;
        } else if (c2 > c1) {
            return 0;
        }
    }

    if (t1 == 2) {
        int c1, d1, c2, d2;
        for (int i = 0; i<15; i++) {
            if (card1Freq[i] == 2) {
                c1 = i;
                break;
            }
            if (card2Freq[i] == 2) {
                c2 = i;
                break;
            }
        }
        for (int i = 0; i<15; i++) {
            if (card1Freq[i] == 2) {
                d1 = i;
            }
            if (card2Freq[i] == 2) {
                d2 = i;
            }
        }
        if (d1 > d2) {
            return 1;
        } else if (d2 > d1) {
            return 0;
        }
        if (c1 > c2) {
            return 1;
        } else if (c2 > c1) {
            return 0;
        }
    }

    for (int i = 4; i>=0; i--) {
        if (hand1[i].value > hand2[i].value) {
            return 1;
        }
        if (hand2[i].value > hand1[i].value) {
            return 0;
        }
    }
    return 0;
}

int main(void) {
    char *buff;
    FILE *f = fopen("../files/0054_poker.txt", "r");
    if (f == NULL) {
        printf("Error opening input file!");
        return 1;
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    buff = malloc(len);
    fread(buff, 1, len, f);

    Card games[1000][2][5];

    for (int i = 0; i<len; i+=3) {
        games[i/30][((i/3)%10)/5][(i/3)%5] = createCard(buff[i],buff[i+1]);
    }

    int n = 0;

    for (int i = 0; i<1000; i++) {
        n += (winner(games[i][0], games[i][1]));
    }

    printf("%d\n", n);

    free(buff);
    return 0;
}