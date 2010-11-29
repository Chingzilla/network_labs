# src/Makefile

all:	server client

server: movies.o
	gcc -std=c99 server.c movies.o -o server

client:
	gcc -std=c99 client.c -o client

movies.o: movies.c
	gcc -std=c99 -c movies.c

clean:
	rm -f *.h.gch
	rm -f *.o

purge:	clean
	rm client
	rm server
