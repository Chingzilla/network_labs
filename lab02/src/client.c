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

#define MAXMOVIESIZE 128

int main(int argc, char *argv[]){
    // Open socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("socket not opened");
        exit(-1);
    }
    
    // Connect to server
    SA_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(ADDRESS);
    
    // test connection
    if (connect(sock, (SA *)&addr, sizeof(SA_IN) < 0)){
        perror("on connect");
        exit(-1);
    }

    printf("Connected to %s\n", ADDRESS);

    char movie_title[MAXMOVIESIZE];

    while(1){
        //Get Movie name, exit if EOF is entered
        printf("Enter a Moive:");
        
	if (gets(movie_title) == NULL){
            printf("Client closeing");
	    break;
        }

        //Request Movie
	if (send(sock, movie_title, strlen(movie_title), 0) == -1){
		perror("send");
	}

	//Get replay
	if ( recv(sock, movie_title, MAXMOVIESIZE - 1, 0) == -1){
		perror("recv");
		exit(1);
	}

	//Print reply
	printf("%s\n", movie_title);
    }

    //Close Connection and return
    close(sock);
    return 0;
}
