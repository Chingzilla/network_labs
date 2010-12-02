/*
 * src/cards.h
 * Chris Ching
 */

#ifndef CARDS_H
#define CARDS_H


#define MAXCARDS 52

#define SPADES   0
#define HEARTS   1
#define DIAMONDS 2
#define CLUBS    3

#define JACK     11
#define QUEEN    12
#define KING     13

/* Storage structor for card
 * face_value is in range 1-52
 * card_value%card_name returns card value
 * card_value/card_suit returns card's suit
 */
typedef struct card{
    int face_value;
    char string[10];
    struct card * next_card;
} card;

typedef struct carddeck{
    card * top_card;
    card * bottom_card;
    int    total_cards;
} carddeck;

// Returns a string recentation of that card
char * cardToString(card *);

char * deckToString(char *, carddeck);

int    isJack(int);

// Shuffles that given deck
carddeck * shuffle(carddeck *);

// Returns the number of cards in a deck
int countCards(carddeck *);

#endif