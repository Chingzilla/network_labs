#Makefile
#Chris Ching

all: server client

server: server.c connection.o game.o
	gcc -o server server.c connection.o game.o

client: client.c connection.o
	gcc -o client client.c connection.o
	
connection.o:
	gcc -c connection/connection.c

game.o:
	gcc -c game/game.c

clean:
	rm *.o

purge: clean
	rm -f client
	rm -f server
