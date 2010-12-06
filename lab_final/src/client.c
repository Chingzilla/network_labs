/*
 * src/client/client.c
 */

#include "connection/connection.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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

// Returns the socket number
int getServer(){
    int sockfd = 0;
    struct sockaddr_storage server_addr;
    
    getServerIP(&server_addr);   
 
    return sockfd;
}


int main(int argc, char *argv[]){

    int sockfd;

    sockfd = getServer();
//    int sockfd;
//    struct sockaddr_in server_addr;
//    struct hostend *he;
//    
//    int numbytes;
//    int broadcast = 1;
//
//    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
//        perror("socket");
//        exit(1);
//    }
//
//    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
//            sizeof broadcast) == -1)
//    {
//        perror("setsock (SO_BROADCAST)");
//        exit(1);
//    }
//
//    if ((he=(struct hostend *)gethostbyname("255.255.255.255")) == NULL){
//       perror("gethostbyname");
//       exit(1);
//    }
//
//    server_addr.sin_family = AF_INET;
//    server_addr.sin_port = htons(BROADCASTPORT);
//    inet_aton("255.255.255.255", &server_addr.sin_addr);
//    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
//    
//
//    //request server ip
//    if ((numbytes=sendto(sockfd, REQUESTMSG, strlen(REQUESTMSG), 0,
//            (struct sockaddr *) &server_addr, sizeof server_addr)) == -1){
//        perror("sendto");
//        exit(1);
//    }
//    
//    //get server ip
//    addr_len = sizeof their_addr;
//    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
//        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
//        perror("recvfrom");
//        exit(1);
//    }
//
//    printf("listener: got packet from %s\n",
//        inet_ntop(their_addr.ss_family,
//            get_in_addr((struct sockaddr *)&their_addr),
//            s, sizeof s));
//    printf("listener: packet is %d bytes long\n", numbytes);
//    buf[numbytes] = '\0';
//    printf("listener: packet contains \"%s\"\n", buf);
}
