
#include "connection.h"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int setup_connection(int * sockfd,
                     int portnum,
                     struct addrinfo hints;
                     struct addrinfo * p){

    struct addrinfo *servinfo;
    int rv;

    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
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
