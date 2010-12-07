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
    char buf[MAXBUF];

    SELF.sockfd = sockfd;

    //get player's name
    Send(SELF.sockfd, "Enter Player Name");
    Recv(SELF.sockfd, SELF.name);

    sprintf(buf, "Welcome %s", SELF.name);
    Send(SELF.sockfd, buf);
}

void playerLobby(){
}
