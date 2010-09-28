# Makefile
# Jakub Gedeon, CS201, Lab9
# 3/24/09

all: server client

server: server.o
	gcc -o server server.o

server.o: server.c
	gcc -c server.c shared.h

client: client.o
	gcc -o client client.o

client.o: client.c
	gcc -c client.c shared.h

clean:
	rm *.o *.h.gch
	
purge: clean
	rm client server
