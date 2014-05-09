CC=gcc
CFLAGS=-Wall
LIBS=-lmcrypt

all: server client

client: client.o encrypt.o
	$(CC) $(CFLAGS) -o $@  $^ -lrt $(LIBS)

client.o: client.c
	$(CC) $(CFLAGS) -c -o $@ $<

server: server.o encrypt.o
	$(CC) $(CFLAGS) -o $@  $^ -lrt $(LIBS)

server.o: server.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f server client
