/* server1.c 
 */

#include "connection.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
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
    * Bind a name to the socket.  Since the server will bind with
    * any client, the machine address is zero or INADDR_ANY.  The port
    * has to be the same as the client uses.
    */
   SA_IN addr;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT_NUM);
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

   /*
    * Wait for a client to connect.  When this happens, print out a 
    * message including the address of the client.  Note that clientsock
    * is a socket just like sock, except that it is specifically connected
    * to the client.  sock is used just to get connections.
    */
   socklen_t addrsize = sizeof(SA_IN); 
   int clientsock = accept(sock, (SA *)&addr, &addrsize);
   if (clientsock < 0) {  
      perror("on accept");
      exit(-1);
   }
   printf(" --> connection made with client %s\n", inet_ntoa(addr.sin_addr));

   /*
    * Print messages from client. Note that the messages are processed
    * one character at a time due to the nature of stream communication.
    * There is no end-of-message type of character, and part of a message
    * could arrive, or serveral messages could arrive together.  Therefore
    * look for the null character ('\0'), which the client has to send.
    */
   int mlen;
   while (mlen = recv(clientsock, buf, MAXBUFFSIZE, 0)) {
       for (int c = 0; c < mlen; ++c) {
	   if (buf[c] == '\0') {
	       putchar('\n');
	   } else {
	       putchar(buf[c]);
	   }
       }
   }
   printf(" --> all messages read - connection being closed\n");

   /*  
    * Shutdown the socket to insure that it is handled properly, and then
    * close the client socket and also the server socket 
    */
   shutdown(clientsock, SHUT_RDWR);
   close(clientsock);
   close(sock);
}
