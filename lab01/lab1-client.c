/* ========================================================> client1.c 
 * Simple client model for Internet communication using stream sockets.
 * This program simply accesses a server socket and writes a few messages.
 * Then it closes the socket and terminates.
 * ====================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define  SA     struct sockaddr
#define  SA_IN  struct sockaddr_in


int main(int argc, char *argv[])
{
   /* 
    * Open a socket for Internet stream services.
    */
   int sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock < 0) {
       perror("opening socket");
       exit(-1);
   }

   /*
    * The address structure requires an address family (Internet), a port
    * for the server (540) and an address for the machine (esus is
    * 153.90.192.1).  Note that anyting that is not defined or a byte
    * should be converted to the appropriate network byte order.  Look
    * in in.h to see the address structure itself.  Just for fun, look at the
    * function inet_addr and see if you can convert 153.90.192.1 to
    * the address more easily.
    */
   SA_IN addr;
   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(44444);
   unsigned int in_address = 153 << 24 | 90 << 16 | 102  << 8 | 73;
   addr.sin_addr.s_addr = htonl(in_address);
   if (connect(sock, (SA *)&addr, sizeof(SA_IN)) < 0) {   
      perror("on connect");
      exit(-1);
   } 

   /* 
    * Write a few simple messages. Note that the null character at
    * the end of the string is included in the message length by adding
    * 1 to the total character count of the message.  Obviously this can
    * be done better by using strlen, but it makes a point.
    */ 
   send(sock, "client calling server, do you read me", 38, 0);
   send(sock, "the socket is operational", 26, 0);
   send(sock, "client is not reading the socket, but it could", 47, 0);
   send(sock, "client terminating session", 27, 0);

   /* 
    * Do a shutdown on the write half of the socket to gracefully terminate by
    * saying - "no more data" and then close the socket -- the shutdown is
    * optional in a one way communication that is going to terminate, but it
    * has its uses - see page 172 for all the details.
    */
   if (shutdown(sock, SHUT_WR) < 0) {  
      perror("on shutdown");
      exit(-1);
   }
   printf ("Client is done\n");
   close(sock);
}
