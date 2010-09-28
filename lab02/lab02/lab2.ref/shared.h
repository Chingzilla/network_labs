/*
** shared.h -- shared defines and includes
**   by Jakub
*/

#ifndef _SHARED_H
#define _SHARED_H

// the port client will be connecting to 
#define PORT "55555"
// max number of bytes we can get at once 
#define MAXDATASIZE 100
// how many pending connections queue will hold
#define BACKLOG 10
#define FILENAME "movies.txt"

// Basic funcionality libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Client and server networking libraries
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Server only stuff???
#include <sys/wait.h>
#include <signal.h>

#endif
