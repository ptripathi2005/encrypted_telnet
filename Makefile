CC=gcc
CFLAGS=-Wall
#LIBS=-lmcrypt

LIBS := -lmcrypt
OS := $(shell uname -s)
ifeq ($(OS),Linux)
LFLAGS += -lrt
endif

all: server client

client: client.o encrypt.o
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

client.o: client.c
	$(CC) $(CFLAGS) -c -o $@ $<

server: server.o encrypt.o
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

server.o: server.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f server client
