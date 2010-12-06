
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

int buildGamePort(struct GameProt * self){
    sprintf(SELF.raw_str, "%d:%d:%d:%s", SELF.input_type, SELF.y, SELF.x, SELF.msg);

    return 0;
}
