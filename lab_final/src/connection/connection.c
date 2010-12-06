
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

int gameProtInit(struct GameProt * self, int input_type, int y, int x, char * msg){
    SELF.input_type = input_type;
    SELF.y = y;
    SELF.x = x;
    strcpy(SELF.msg, msg);

    return buildGameProt(self);
}

int parseGameProt(struct GameProt * self){
    char s[MAXBUF];
    char * current_info;

    strcpy(s, SELF.raw_str);

    //Read input type
    current_info = strtok(s, ":");
    if (sprintf(current_info, "%d", SELF.input_type) != 1){
        return 1;
    }

    //Read msg placement
    current_info = strtok(NULL, ":");
    if (sprintf(current_info, "%d", SELF.y) != 1){
        return 2;
    }

    current_info = strtok(NULL, ":");
    if (sprintf(current_info, "%d", SELF.x) != 1){
        return 3;
    }

    //Read msg
    current_info = strtok(NULL, "\0");
    strcpy(SELF.msg, current_info);

    return 0;
}

int buildGameProt(struct GameProt * self){
    sprintf(SELF.raw_str, "%d:%d:%d:%s", SELF.input_type, SELF.y, SELF.x, SELF.msg);

    return 0;
}

int sendMsg(struct GameProt * gameP, int sockfd){
    int rv;
    struct pollfd ufds;

    ufds.fd = sockfd;
    ufds.events = POLLOUT;

    //try to send signial, timeout after 5 secs
    rv = poll(&ufds, 1, 5000);
    
    if (rv == -1) {
        perror("poll");
        return rv;
    }
    else if (rv == 0){
        //timed out
        return 1;
    }
    else{
        if (ufds.revents & POLLOUT){
            if (send(sockfd, (*gameP).msg, strlen((*gameP).msg), 0) == -1)
                perror("send");
            return 0;
        }
    }
    return 1;
}

int recvMsg(struct GameProt * gameP, int sockfd, int timeout){

    int rv;
    int numbytes;
    struct pollfd ufds;

    ufds.fd = sockfd;
    ufds.events = POLLIN;

    //try to recive signial
    rv = poll(&ufds, 1, timeout);
    
    if (rv == -1) {
        perror("poll");
        return rv;
    }
    else if (rv == 0){
        //timed out
        return 1;
    }
    else{
        if (ufds.revents & POLLIN){
            numbytes = recv(sockfd, (*gameP).msg, MAXBUF -1, 0);
            if( numbytes == -1){
                perror("recv");
                return 1;
            }
            (*gameP).msg[numbytes] = '\0';
        }
    }
    return 0;
}
