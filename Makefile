ifeq ($(OS),Windows_NT)
	SERVER_EXE = chat-server-win.exe
	CLIENT_EXE = chat-client-win.exe
else
	SERVER_EXE = chat-server-linux.out
	CLIENT_EXE = chat-client-linux.out
endif


all: server client

server: server.o socket_proxy.o list_int.o
	gcc server.o socket_proxy.o list_int.o -o ${SERVER_EXE} -Wall -lpthread

client: client.o socket_proxy.o
	gcc client.o socket_proxy.o -o ${CLIENT_EXE} -Wall -lpthread

server.o: server.c
	gcc -c server.c

client.o: client.c
	gcc -c client.c

socket_proxy.o: socket_proxy.c socket_proxy.h
	gcc -c socket_proxy.c

list_int.o: list_int.c list_int.h
	gcc -c list_int.c


clear:
	rm *.o
