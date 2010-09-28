/*
** client.c -- movie data request client
*/

#include "shared.h"

int main(void)
{
    int sock; // socket for data transfer
    struct addrinfo hints, *servinfo; // used to establish connection
    
    // String data storage
    int numbytes;
    char buf[MAXDATASIZE];

    // Obtain/generate connection information and store it in &servinfo
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo("localhost", PORT, &hints, &servinfo) != 0) {
        perror("client: dns resolve");
        return 1;
    }

    // Create a socket
    if ((sock = socket(servinfo->ai_family, servinfo->ai_socktype,
            servinfo->ai_protocol)) == -1) {
        perror("client: socket");
        return 2;
    }

    // Connect to the server with the socket
    if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(sock);
        perror("client: connect");
        return 3;
    }

    // Delete the connection information structure
    freeaddrinfo(servinfo);
    
    while(1) {
        // Get the querry from the user
        printf("Enter movie name: ");
        fgets(buf, MAXDATASIZE, stdin);
        
        // Cut off the trailing newline
        numbytes = strlen(buf) - 1;
        buf[numbytes] = '\0';
        
        // Send the data
        if (send(sock, buf, strlen(buf), 0) == -1)
            perror("send");
        
        // Print the response
        if ((numbytes = recv(sock, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        buf[numbytes] = '\0';
        printf("%s",buf);
    }
    
    close(sock);

    return 0;
}

