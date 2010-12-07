
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
    sscanf(current_info, "%d", SELF.input_type);

    printf("parse: input_type: %s, %d\n", current_info, SELF.input_type);
    
    //Read msg placement
    current_info = strtok(NULL, ":");
    sscanf(current_info, "%d", SELF.y);
    
    printf("parse: y: %s, %d\n", current_info, SELF.y);

    current_info = strtok(NULL, ":");
    sscanf(current_info, "%d", SELF.x);
    
    printf("parse: x: %d\n", SELF.x);

    //Read msg
    current_info = strtok(NULL, "\0");
    strcpy(SELF.msg, current_info);
    printf("parse: msg: %s\n", SELF.msg);

    printf("%s -> %d, %d, %d, %s",SELF.raw_str, SELF.input_type, SELF.y, SELF.x, SELF.msg);

    return 0;
}

int buildGameProt(struct GameProt * self){
    sprintf(SELF.raw_str, ":%d:%d:%d:%s", SELF.input_type, SELF.y, SELF.x, SELF.msg);

    return 0;
}

int sendMsg(struct GameProt * gameP, int sockfd){
    printf("sendMsg: sending: %s\n", (*gameP).raw_str);
    if (send(sockfd, (*gameP).raw_str, strlen((*gameP).msg), 0) == -1)
        perror("sendMsg");
    return 0;
}

int recvMsg(struct GameProt * gameP, int sockfd, int timeout){
    int numbytes;
            
    numbytes = recv(sockfd, (*gameP).raw_str, MAXBUF -1, 0);
    if( numbytes == 0){
        perror("recvMsg: connection closed");
        close(sockfd);
        exit(0);
    }
    if( numbytes < 0){
        perror("recvMsg");
        return 1;
    }

    (*gameP).raw_str[numbytes] = '\0';
    printf("rescMsg: %s\n", (*gameP).raw_str);
    //Parse out msg
    if( parseGameProt(gameP) !=0 ){
        return 1;
    }
    return 0;
}
