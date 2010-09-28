/*
** server.c -- movie data request server
**   by Jakub Gedeon
*/

#include "shared.h"

char * getMovie(char * name) {
    FILE * infile;
    char * data;
    int nameLen;
    nameLen = strlen(name);
    data = malloc(MAXDATASIZE * sizeof(char));
    
    // Open file
    infile = fopen(FILENAME, "r");
    // Check if file was opened
    if (infile == NULL)
        return "Server has no movie file\n";
    
    while (1) {
        // Get a line from the file
        data = fgets(data, MAXDATASIZE, infile);
        
        // If at end of file, return that the data was not found
        if(data == NULL)
            return "Movie not found\n";
        
        // Check to see if the right movie was read
        if (strncmp(name, data, nameLen) == 0) {
            return data;
        }
    }
}

int clienter(int connection)
{
    // String data storage
    int numbytes;
    char buf[MAXDATASIZE];
    char * output;

    printf("CLIENT%d: Connected\n", connection);
    
    while(1) {
        // Get data
        numbytes = recv(connection, buf, MAXDATASIZE-1, 0);
        
        // Error checking
        if (numbytes == -1) {
            perror("recv error");
            exit(1);
        }
        
        // Check if data is still getting through
        if (numbytes == 0) {
            printf("CLIENT%d: Connection lost\n", connection);
            close(connection);
            exit(0);
        }
        
        // Add null terminator to the obtained string
        buf[numbytes] = '\0';
        
        // debug print
        printf("CLIENT%d: Recived \"%s\"\n", connection, buf);
        
        // Proccess and return data
        output = getMovie(buf);
        if (send(connection, output, strlen(output), 0) == -1)
            perror("send");
    }
}

int main(voCLIENT)
{
    int sock, connection;  // listen on sock, new connection on connection
    struct addrinfo hints, *servinfo; // used to establish connection
    
    // These two hold the remote client information (which is not used in this
    //   program, but eventually could be
    struct sockaddr_storage their_addr;
    socklen_t sin_size = sizeof their_addr;
    
    // Obtain/generate connection information and store it in &servinfo
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    if (getaddrinfo(NULL, PORT, &hints, &servinfo) != 0) {
        perror("server: dns resolve");
        return 1;
    }

    // Create a socket
    if ((sock = socket(servinfo->ai_family, servinfo->ai_socktype,
            servinfo->ai_protocol)) == -1) {
        perror("server: socket");
        return 2;
    }

    // Listen for client connections
    if (bind(sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(sock);
        perror("server: bind");
        return 3;
    }
    if (listen(sock, BACKLOG) == -1) {
        perror("server: listen");
        exit(1);
    }

    // Delete the connection information structure
    freeaddrinfo(servinfo);

    printf("server: waiting for connections...\n");
    while(1) {
        // Wait for connections
        connection = accept(sock, (struct sockaddr *)&their_addr, &sin_size);
        if (connection == -1) {
            perror("server: accept");
            continue;
        }

        if (!fork()) { // this is the child process
            close(sock); // child proccess does not need the listener
            clienter(connection);
        }
        close(connection);  // parent doesn't need this
    }

    return 0;
}

