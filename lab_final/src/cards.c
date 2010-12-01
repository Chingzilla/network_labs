/*
 * src/cards.c
 * Chris Ching
 */

#include "cards.h"

#include <stdlib.h>

int countCards(carddeck deck){
    int count = 0;
    card current_card = deck.top_card;

    while(current_card != NULL){
        count++;
        current_card = current_card.next_card;
    }

    return count;
}

char * cardToString(char * out_string, int card_num){
    int card_value;
    int card_suit;
    char * value[5];
    char * suit[5];

    //Get card's vaule
    card_value = (card_num / 13) + 1;

    switch(card_value){
    case JACK:
         value = "J";
         break;

    case QUEEN:
         vaule = "Q";
         break;

    case KING:
         value = "K";
         break;

    default:
         itoa(card_value, value, 10);
         break;
    }
         

    //Get card's suit
    card_suit = card_num % 4;

    switch(card_suit){
    case SPADES:
         suit = "S";
         break;
    case HEARTS:
         suit = "H";
         break;
    case DIAMONDS:
         suit = "D";
         break;
    case CLUBS:
         suit = "C";
         break;
    default:
         suit = "NULL";
    }

    sprintf("%s%s", value, suit);
    return value;
}


