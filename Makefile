all: server client

server: server.o socket_proxy.o list_int.o
	gcc server.o socket_proxy.o list_int.o -o server-linux.out -Wall -lpthread

client: client.o socket_proxy.o
	gcc client.o socket_proxy.o -o client-linux.out -Wall -lpthread

server.o: server.c
	gcc -c server.c

client.o: client.c
	gcc -c client.c

socket_proxy.o: socket_proxy.c socket_proxy.h
	gcc -c socket_proxy.c

list_int.o: list_int.c list_int.h
	gcc -c list_int.c

## WINDOWS
windows: server-win client-win

server-win: server.c socket_proxy.c socket_proxy.h list_int.c list_int.h
	x86_64-w64-mingw32-gcc server.c socket_proxy.c list_int.c -o server-win.exe

client-win: client.c socket_proxy.c socket_proxy.h
	x86_64-w64-mingw32-gcc client.c socket_proxy.c -o client-win.exe