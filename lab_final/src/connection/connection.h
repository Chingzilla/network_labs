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

#define MAXBUF 180
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

void Send(int, char *);
void Recv(int, char *);

#endif //_CONNECTION_H
