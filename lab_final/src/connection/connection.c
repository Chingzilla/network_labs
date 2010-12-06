
#include "connection.h"

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

int setup_connection(int * sockfd,
                     char * portnum,
                     char * ip_addr, //set to NULL for localhost
                     struct addrinfo hints,
                     struct addrinfo * p){

    struct addrinfo *servinfo;
    int rv;

    if ((rv = getaddrinfo(ip_addr, portnum, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if (((*sockfd) = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("setup_connection: socket");
            continue;
        }

        if (bind((*sockfd), p->ai_addr, p->ai_addrlen) == -1) {
            close((*sockfd));
            perror("setup_connection: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "setup_connection: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);
    
    return 0;
}

int Send(int sockfd, char * msg){
    if(send(sockfd, msg, strlen(msg), 0) == -1){
        perror("Send");
        return 1;
    }
}

int SendTo(int sockfd, char * msg, struct addrinfo dest_addr){
    int numbytes;
    numbytes = sendto(sockfd, msg, strlen(msg), 0, dest_addr.ai_addr, dest_addr.ai_addrlen);
    
    if((numbytes)== -1){
        perror("SendTo");
    }
    return numbytes;
}
