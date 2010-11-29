//Connection information
//Chris Ching


#ifndef CONNECTION_C
#define CONNECTION_C

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT "55555"
#define ADDRESS "127.0.0.1"

#define MAXBUFFSIZE 128

#define SA      struct sockaddr
#define SA_IN   struct sockaddr_in

#endif	// CONNECTION_C
