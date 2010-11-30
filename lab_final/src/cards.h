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
typedef struct{
    int face_value;
    card * next_card;
} card;

typedef struct{
    card * top_card;
    card * bottom_card;
    int    total_cards;
} carddeck;

// Returns a string recentation of that card
char * cardToString(char *, int);

char * deckToString(char *, int);

bool   isJack(int);

// Shuffles that given deck
carddeck * shuffle(carddeck *);

// Returns the number of cards in a deck
int countCards(carddeck);

#endif
