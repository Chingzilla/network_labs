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
