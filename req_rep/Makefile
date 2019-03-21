.PHONY: all clean
SRCS := server.c client.c

all: server client

server: server.c
	gcc -o server server.c -lzmq

client: client.c
	gcc -o client client.c -lzmq

clean:
	rm -f server client

