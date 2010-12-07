
#include "connection.h"
#include "../class.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void sigchld_handler(int s){
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

void Send(int sockfd, char * msg){
    if( send(sockfd, msg, strlen(msg), 0) == 0){
        //Connection closed
        exit(1);
    }
}

void Recv(int sockfd, char * msg){
    recv(sockfd, msg, MAXBUF -1, 0);
}
