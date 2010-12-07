/*
 * src/client/client.c
 */

#include "connection/connection.h"
#include "class.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <curses.h>


int getServerIP(struct sockaddr_storage * server_addr){
    int sockfd;
    struct sockaddr_in their_addr; // connector's address information
    struct hostent *he;
    int numbytes;
    int broadcast = 1;

    if ((he=gethostbyname("255.255.255.255")) == NULL) {  // get the host info
        perror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // this call is what allows broadcast packets to be sent:
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof broadcast) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

    their_addr.sin_family = AF_INET;     // host byte order
    their_addr.sin_port = htons(BROADCASTPORT); // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

    printf("Requesting server on port:%d\n", BROADCASTPORT);

    if ((numbytes=sendto(sockfd, REQUESTMSG, strlen(REQUESTMSG), 0,
             (struct sockaddr *)&their_addr, sizeof their_addr)) == -1) {
        perror("sendto");
        exit(1);
    }

    //Get server ip
    int addr_len = sizeof * server_addr;
    char s[INET6_ADDRSTRLEN];
    char buf[MAXBUF];

    if((numbytes = recvfrom(sockfd, buf, MAXBUF-1, 0,
        (struct sockaddr *)server_addr, &addr_len)) == -1){
        perror("recvfrom");
        exit(1);
    }

    inet_ntop((*server_addr).ss_family,
        get_in_addr((struct sockaddr *) server_addr),
        s, sizeof s);

    printf("Server IP: %s\n", s);

    close(sockfd);
}

int connectToServer(int * sockfd, struct sockaddr_storage server_addr, struct addrinfo *p){
    int numbytes;  
    char buf[MAXBUF];
    struct addrinfo hints, *servinfo;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    inet_ntop(server_addr.ss_family,
        get_in_addr((struct sockaddr *) &server_addr),
        s, sizeof s);

    if ((rv = getaddrinfo(s, GAMEPORT_STR, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((*sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(*sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(*sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    gameTerm(*sockfd);

    return 0;    
}

// Returns the socket number
int getServer(){
    int sockfd = 0;

    struct addrinfo p;
    struct sockaddr_storage server_addr;
    
    getServerIP(&server_addr);   
 
    connectToServer(&sockfd, server_addr, &p);

    gameTerm(sockfd);
    return 0;
}

//Creates a dump terminal
int gameTerm(int sockfd){

    //Setup polling
    struct pollfd io[2];
    int nready;
    int numbytes;

    char msg_in[MAXBUF];
    char msg_out[MAXBUF];

    // io[0] == stdin
    io[0].fd = fileno(stdin);
    io[0].events = POLLIN;
    // io[1] == socket
    io[1].fd = sockfd;
    io[1].events = POLLIN;

    while(1){
        nready = poll(io, 2, -1);
        if( nready == -1){
            perror("poll");
        }
        else{
            if(io[0].revents & POLLIN){
                fgets(msg_out, MAXBUF, stdin);
                //Remove new line
                msg_out[strlen(msg_out) -1] = '\0';

                //send
                if( send(sockfd, msg_out, strlen(msg_out), -1) == 0){
                    //Connection closed
                    exit(1);
                }
            }

            if(io[1].revents & POLLIN){
                numbytes = recv(sockfd, msg_in, MAXBUF -1, 0);
                if(numbytes == 0){
                    //Connection closed
                    exit(1);
                }
                msg_in[numbytes] = '\0';

                printf("%s\n", msg_in);
            }
        }
    }

    perror("recv/send");
    exit(1);
}

int main(int argc, char *argv[]){

    int sockfd;

    sockfd = getServer();
}
