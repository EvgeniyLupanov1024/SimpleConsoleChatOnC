all: server client

server: server.o socket_error_proxy.o list_int.o
	gcc server.o socket_error_proxy.o list_int.o -o server.exe -Wall -lpthread

client: client.o socket_error_proxy.o
	gcc client.o socket_error_proxy.o -o client.exe -Wall -lpthread

server.o: server.c
	gcc -c server.c

client.o: client.c
	gcc -c client.c

socket_error_proxy.o: socket_error_proxy.c socket_error_proxy.h
	gcc -c socket_error_proxy.c

list_int.o: list_int.c list_int.h
	gcc -c list_int.c