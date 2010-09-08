/* ======================================================> server1.c 
 * Generic sort of server process for Unix 
 *
 * This is an extremely simple use of sockets for communication.
 * The server opens a socket and then reads messages and prints them out
 * without further ado until the client closes the socket. 
 * =====================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

#define  SA     struct sockaddr
#define  SA_IN  struct sockaddr_in

#define  BUF_SIZE  80

#define  PORT 44444

int main(int argc, char *argv[])
{

    char buf[BUF_SIZE+1];

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
   while (mlen = recv(clientsock, buf, BUF_SIZE, 0)) {
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
