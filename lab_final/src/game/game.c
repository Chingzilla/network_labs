/*
 * src/game/game.c
 * Chris Ching
 */

#include "game.h"
#include "../connection/connection.h"
#include "cards.h"
#include "../class.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


/********************
 *   Player Class   *
 ********************/

void playerInit(int sockfd){
    Player * self;
    GameProt gameP;
    
    SELF.sockfd = sockfd;

    //get player's name
    gameProtInit(&gameP, INPUTTYPE_STR, 4, 0, "Enter Player Name");
    printf("sending to client: %s", *gameP.raw_str);
    
    sendMsg(&gameP, SELF.sockfd);
    recvMsg(&gameP, SELF.sockfd, -1);

    strncpy(SELF.name, gameP.msg, sizeof SELF.name);

}

void playerLobby(){
}
