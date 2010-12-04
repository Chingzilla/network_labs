/*
 * src/client/client.c
 */

#include "connection/connection.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>



int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;
    struct hostend *he;
    
    int numbytes;
    int broadcast = 1;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
            sizeof broadcast) == -1) {
        perror("setsock (SO_BROADCAST)");
        exit(1);
    }

    if ((he=(struct hostend *)gethostbyname("255.255.255.255")) == NULL){
       perror("gethostbyname");
       exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(BROADCASTPORT);
    inet_aton("255.255.255.255", &server_addr.sin_addr);
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
    

    //get server ip
    if ((numbytes=sendto(sockfd, REQUESTMSG, strlen(REQUESTMSG), 0,
            (struct sockaddr *) &server_addr, sizeof server_addr)) == -1){
        perror("sendto");
        exit(1);
    }
}
