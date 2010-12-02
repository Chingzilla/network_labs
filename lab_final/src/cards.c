/*
 * src/cards.c
 * Chris Ching
 */

#include "cards.h"

#include <stdlib.h>

#define SELF (* self)

/************************
 * Class card           *
 ************************/
card * cardInit(card * self, int face_value){
    if(self == NULL){
        self = malloc(sizeof(self));
    }
    SELF.face_value = face_value;
    SELF.next_card = NULL;
    cardToString(self);
}

char * cardToString(card * self){
    int card_value;
    int card_suit;
    char * value;
    char * suit;

    //Get card's vaule
    card_value = (SELF.face_value / 13) + 1;

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
    card_suit = SELF.face_value % 4;

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

    sprintf(SELF.string, "%s%s", value, suit);
    return SELF.string;
}

/*********************
 * Class carddeck    *
 *********************/
carddeck * deckInit(carddeck * self){
    if(self == NULL){
        self = malloc(sizeof(self));
    }
    SELF.top_card = NULL;
    SELF.bottom_card = NULL;
    SELF.total_cards = 0;
    SELF.string = (char *)malloc(sizeof(char) * 80);
}

char * deckToString(carddeck * self){
    card current_card;
    current_card = * SELF.top_card;

    SELF.string = "";
    int i;
    for(i = 0; i < SELF.total_cards; i++){
        strcat(SELF.string, current_card.string);
        strcat(SELF.string, " ");

        //Get next card
        if(current_card.next_card == NULL){
            break;
        }

        current_card = *(current_card.next_card);
    }
    return SELF.string;
}


