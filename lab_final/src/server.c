/*
 * src/server.c
 * Chris Ching
 */

#include "connection/connection.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//Based on listener.c from beeq.us
int broadcastIP(){
    int sockfd;
    int rv;
    struct addrinfo hints, *servinfo, *p;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUF];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, BROADCASTPORT_STR, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("broadcastIP: socket");
            continue;
        }
    
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("broadcastIP: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "broadcastIP: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    printf("broadcastIP: waiting to recvfrom...\n");

    //Keep broadcasting forever
    while(1){
        addr_len = sizeof their_addr;
        if ((numbytes = recvfrom(sockfd, buf, MAXBUF-1 , 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }
        //See if valid request
        if(strcmp(buf, REQUESTMSG) != 0){
            printf("broadcastIP: invalid request\n");
            continue;
        }

        printf("broadcastIP: got request packet from %s\n",
            inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof s));

        //Send ip
        if(sendto(sockfd, ACKMSG, strlen(ACKMSG), 0, (struct sockaddr *)&their_addr,
                sizeof their_addr) == -1){
            perror("broadcastIP: sendto");
        }
    }
    //This should never run
    close(sockfd);
    return 0;
}

int main(){
    
    //Start udp broadcast sub-process
//    if(fork() == 0){
        //In child process
        broadcastIP();
        exit(0);
//    }
}
