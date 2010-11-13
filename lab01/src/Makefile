# src/Makefile

all:	server client

server:
	gcc -std=c99 server.c -o server

client:
	gcc -std=c99 client.c -o client

clean:
	rm -f *.h.gch
	rm -f *.o

purge:	clean
	rm client
	rm server
