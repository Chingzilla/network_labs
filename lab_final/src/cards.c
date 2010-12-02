/*
 * src/cards.c
 * Chris Ching
 */

#include "cards.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    //Get card's vaule
    int card_value;
    card_value = (SELF.face_value / 13) + 1;

    switch(card_value){
    case JACK:
         strcpy(SELF.string, "J");
         break;

    case QUEEN:
         strcpy(SELF.string, "Q");
         break;

    case KING:
         strcpy(SELF.string, "K");
         break;

    default:
         sprintf(SELF.string, "%d", card_value);
         break;
    }
         

    //Get card's suit
    int card_suit;
    card_suit = SELF.face_value % 4;

    switch(card_suit){
    case SPADES:
         strcat(SELF.string, "S");
         break;
    case HEARTS:
         strcat(SELF.string, "H");
         break;
    case DIAMONDS:
         strcat(SELF.string, "D");
         break;
    case CLUBS:
         strcat(SELF.string, "C");
         break;
    default:
         strcat(SELF.string, "#");
    }

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
    strcpy(SELF.string, "");
}

carddeck * deckAddCard(carddeck * self, card * new_card){
    //If empty deck, start a new one
    if(SELF.top_card = NULL){
        SELF.top_card = new_card;
        SELF.bottom_card = new_card;
        SELF.total_cards = 1;
    }
    //If deck has cards it in, add to bottom and recount
    SELF.bottom_card = new_card;
    SELF.total_cards++;

    card temp_card = *SELF.bottom_card;
    while(temp_card.next_card != NULL){
        SELF.total_cards++;
        temp_card = *(temp_card.next_card);
    }

    //Update string
    deckToString(self);

    return self;
}

card * deckPopCard(carddeck * self){
    card * this_card;
    this_card = SELF.top_card;

    SELF.top_card = (*SELF.top_card).next_card;

    SELF.total_cards--;

    return this_card;
}

char * deckToString(carddeck * self){
    card current_card;
    current_card = * SELF.top_card;

    SELF.string[0] = '\0';
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


