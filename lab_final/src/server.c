/*
 * src/server.c
 * Chris Ching
 */

#include "connection/connection.h"
#include "game/game.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/wait.h>
#include <signal.h>

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
    hints.ai_family = AF_INET; // set to AF_INET to force IPv4
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

int acceptConnections(){

    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, GAMEPORT_STR, &hints, &servinfo)) != 0) {
        fprintf(stderr, "acceptConnections: getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("acceptConnections: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("acceptConnections: setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("acceptConnections: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("acceptConnections: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("acceptConnections: %s connected\n", s);

        if (!fork()) { // this is the child process
            //close(sockfd); // child doesn't need the listener

            //Add player to lobby
            playerInit(new_fd);
            
            close(new_fd);
            exit(0);
        }
        printf("Closeing socket %d\n", new_fd);
        close(new_fd);  // parent doesn't need this
    }    
    
    return 0;
}

int main(){
    
    //Start udp broadcast sub-process
    if(fork() == 0){
        //In child process
        broadcastIP();
        exit(1);    
    }

    //Start TCP listener
    else if(fork() == 0){
        acceptConnections();
        exit(1);          
    }
    sleep(-1);
}
