/* server1.c 
 */

#include "connection.h"
#include "movies.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>

// Represents one client
int client(int connection){
	char in_buff[MAXBUFFSIZE];
	char out_buff[MAXBUFFSIZE];
	int buf_size;

	printf("Client %d connected\n", connection);

	while(1){
		buf_size = recv(connection, in_buff, MAXBUFFSIZE-1, 0);

		//Print data recived
		printf("Client %d sent: %s\n", connection, in_buff);

		//Exit if 'quit' is sent
		if(strcmp(in_buff, "quit")){
			printf("Client %d sent quit signal\n");
			break;
		}
		//return movie data
		searchMovies(in_buff, out_buff);

		//send data
		if(send(connetion, out_buff, strlen(out_buff), 0) == -1)
			perror("send");
	}
	return 0;
}

int main(int argc, char *argv[])
{

    /*
     * Init movies database
    */
    movies_init(NULL);

    char buf[MAXBUFFSIZE+1];

   /*
    * Create the server (listen) socket.
    */
   int sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock < 0) {   
      perror("opening socket");
      exit(-1);
   }

   /*
    * Bind a name to the socket.
    */
   SA_IN addr;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);

   if (bind(sock, (SA *)&addr, sizeof(SA_IN)) < 0) {  
      perror ("on bind -- see me if you get this error");
      exit (-1);
   }

   /*
    * Make the socket available for potential clients.
    */
   if (listen(sock, 5) < 0) {  
      perror("on listen");
      exit(-1);
   }


   printf("Server Initilized, waiting...\n");
   // Enter inf loop
   while(1){
	   /*
	    * Wait for a client to connect.
	    */
	   socklen_t addrsize = sizeof(SA_IN); 
	   int clientsock = accept(sock, (SA *)&addr, &addrsize);
	   if (clientsock < 0) {  
	      perror("on accept");
	      exit(-1);
	   }
	   printf(" --> connection made with client %s\n", inet_ntoa(addr.sin_addr));

	   if ( fork() == 0){
		close(sock); // close the listening socket for this client
		client(clientsock); // start client logic
	   }
	   close(clientsock); // parent closes connected socket
  }
   close(sock);
   return 0;
}
