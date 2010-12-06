#Makefile
#Chris Ching

all: server client

server: client.c connection.o
	gcc -o server server.c connection.o

client: client.c connection.o
	gcc -o client client.c connection.o

connection.o:
	gcc -c connection/connection.c

clean:
	rm *.o

purge: clean
	rm -f client
	rm -f server
