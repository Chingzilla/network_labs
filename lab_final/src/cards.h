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
    char string[4];
    struct card * next_card;
} card;

//Class card methods
char * cardToString(card *);
card * cardInit(card *, int);

typedef struct carddeck{
    card * top_card;
    card * bottom_card;
    int    total_cards;
    char string[80];
} carddeck;

//Class deck methods
char * deckToString(carddeck *);
carddeck * deckInit(carddeck *);
carddeck * deckAddCard(carddeck *, card *);
card *     deckPopCard(carddeck *);
carddeck * deckShuffle(carddeck *);

// Misc methods
int    isJack(int);

#endif
