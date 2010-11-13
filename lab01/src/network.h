 
/* src/network.h
 * Used to store common varables for networking parts
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define	SA	struct sockaddr
#define SA_IN	struct sockaddr_in

#define	BUF_SIZE	80

#define PORT_NUM	55555
#define DEFAULT_IP	"127.0.0.1"

#endif
