/*
 * src/connection/connection.h
 * Chris Ching
 */

#ifndef _CONNECTION_H
#define _CONNECTION_H

#define BROADCASTPORT 54544
#define GAMEPORT 54545
#define REQUESTMSG "REQUESTING_GAME"
#define MAXBUF 128
#define AF_INET_TYPE AF_INET

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa);

int setup_connection(int * sockfd,
                     int portnum,
                     char * ip_addr,
                     struct addrinfo hints,
                     struct addrinfo * p);

int Send(int sockfd, char * msg);
int SendTo(int sockfd, char * msg, struct addrinfo dest_addr);

#endif //_CONNECTION_H
