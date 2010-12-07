/*
 * src/connection/connection.h
 * Chris Ching
 */

#ifndef _CONNECTION_H
#define _CONNECTION_H

#define BROADCASTPORT 54544
#define BROADCASTPORT_STR "54544"
#define GAMEPORT 54545
#define GAMEPORT_STR "54545"

#define REQUESTMSG "REQUESTING_GAME"
#define ACKMSG "REQUEST_RECIVED"

#define MAXBUF 512
#define AF_INET_TYPE AF_INET

#define BACKLOG 10

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/poll.h>

#include "../game/game.h"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa);

void sigchld_handler(int s);

//Protical Stuff
#define INPUTTYPE_CHAR 1
#define INPUTTYPE_STR  2
#define INPUTTYPE_NONE 3
#define INPUTTYPE_WAIT 4

typedef struct GameProt {
    //curses position
    int x;
    int y;

    //Input Type;
    int input_type;

    //String to output;
    char msg[MAXBUF];

    //Raw String from socket
    char raw_str[MAXBUF];
} GameProt;

int gameProtInit(struct GameProt *, int input_type, int y, int x, char *);

int parseGameProt(struct GameProt *);

int buildGameProt(struct GameProt *);

int sendMsg(struct GameProt *, int sockfd);

int recvMsg(struct GameProt *, int sockfd, int timeout);

#endif //_CONNECTION_H
