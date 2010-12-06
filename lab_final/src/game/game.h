/*
 * src/game/game.h
 * Chris Ching
 */

#ifndef _GAME_H
#define _GAME_H

#define MAXNAMELEN 8

//class Player

typedef struct Player{
    char name[MAXNAMELEN];
    int  sockfd;
} Player;

void playerInit(int);

void playerJoinLobby();

#endif //_GAME_H
