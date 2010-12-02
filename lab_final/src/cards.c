/*
 * src/cards.c
 * Chris Ching
 */

#include "cards.h"

#include <stdlib.h>

int countCards(carddeck * deck){
    int count = 0;
    card * current_card = (*deck).top_card;

    while(current_card != NULL){
        count++;
        current_card = (*current_card).next_card;
    }

    (*deck).total_cards = count;
    return count;
}

char * cardToString(card * c){
    int card_value;
    int card_suit;
    char * value;
    char * suit;

    //Get card's vaule
    card_value = ((*c).face_value / 13) + 1;

    switch(card_value){
    case JACK:
         value = "J";
         break;

    case QUEEN:
         value = "Q";
         break;

    case KING:
         value = "K";
         break;

    default:
         itoa(card_value, value, 10);
         break;
    }
         

    //Get card's suit
    card_suit = (*c).face_value % 4;

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

    sprintf((*c).string, "%s%s", value, suit);
    return (*c).string;
}

char * deckToString(char * out_string, carddeck deck){
    card current_card = &deck.top_card;
    char card_string[10];

    out_string = "";
    int i;
    for(i = 0; i < deck_size; i++){
        strcat(out_string, card_string.string);
        strcat(out_string, " ");

        //Get next card
        if(current_card == NULL){
            break;
        }

        current_card = *(current_card.next_card);
    }
    return out_string;
}


