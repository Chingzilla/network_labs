/* client.c 
 */

#include "connection.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
    // Open socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("socket not opened");
        exit(-1);
    }
    
    // Connect to server
    struct sockaddr addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    // set server IP
    inet_aton(ADDRESS, addr.sin_addr);
    // test connection
    if (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in) < 0){
        perror("didn't connect");
        exit(-1);
    }

    printf("Connected to %s\n", ADDRESS)

    char movie_title[100];

    while(1){
        //Get Movie
        printf("Enter a Moive:");
        scanf("%s", movie_title);

        //Exit if EOF is entered
        if (movie_title[0] == EOF){
            printf("Client closeing");
            close(sock);
        }

        //Request Movie

    }
}
