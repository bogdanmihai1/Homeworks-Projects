CC=gcc
CFLAGS=-I.

client: client.c requests.c helpers.c parsers.c
		$(CC) -o client client.c requests.c helpers.c parsers.c
		
run: client
		./client

clean:
		rm -f *.o client
