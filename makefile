
CC = gcc

all:udp_server udp_client udp_select_client

udp_server:udp_server.o
	$(CC) -o udp_server udp_server.o

udp_client:udp_client.o
	$(CC) -o udp_client udp_client.o

udp_select_client:udp_select_client.o
	$(CC) -o udp_select_client udp_select_client.o

clean:
	rm *.o udp_server udp_client udp_select_client
