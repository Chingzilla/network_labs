#Makefile
#Chris Ching

all: server client

server: client.c
	gcc -std=c99 -o server server.c

client: client.c
	gcc -std=c99 -o client client.c

clean:
	rm *.o

purge: clean
	rm -f client
	rm -f server
