/*
 * src/connection/connection.h
 * Chris Ching
 */

#ifndef _CONNECTION_H
#define _CONNECTION_H

#define BROADCASTPORT 54545
#define GAMEPORT 54545
#define REQUESTMSG "REQUESTING_GAME"
#define MAXBUF 128

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

#endif //_CONNECTION_H
