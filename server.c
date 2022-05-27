#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <stdbool.h>
#include <string.h>

#include <sys/types.h>        
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket_error_proxy.c"
#include "STL/forward_list_int.c"

void init();

void waitNewClientConect();
void waitFreeSocket();
void * forwardingClient(void *arg);

void sendToRoom(char *buf, int nread);
void SendWrapper (int number);

int serverSocket;
struct sockaddr_in addr;
socklen_t addrlen;

int ConnectCount;
forward_list_int connectedClientSocket;

int main()
{
	init();

	serverSocket = Socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM -- TSP

	addr.sin_family = AF_INET; // семейство адресов для IPv4
	addr.sin_port = htons(8011); // порт, который будет слушать сервер
	addrlen = sizeof addr;

	Bind(serverSocket, (struct sockaddr *) &addr, sizeof addr);

	Listen(serverSocket, ConnectCount);

	while(true)
	{
		waitNewClientConect();
	}

	close(serverSocket);
	return 0;
}

void init() 
{
	ConnectCount = 5;
	connectedClientSocket = forward_list_int_init();
}

void waitNewClientConect()
{	
	waitFreeSocket();

	int fd = Accept(serverSocket, (struct sockaddr *) &addr, &addrlen);
	connectedClientSocket.add(fd);

	printf("some one connect\n");

	pthread_t thread;
	pthread_create(&thread, NULL, forwardingClient, &fd);
}

void waitFreeSocket()
{
	while(true)
	{
		if (connectedClientSocket.count >= ConnectCount) {
			sleep(1);
		} else {
			break;
		}
	}
}

void * forwardingClient(void *arg)
{
	int fd = * (int *) arg;
	int nread;

	while(true)
	{
		char buf[256];
		nread = recv(fd, buf, 256, 0);

		if (nread == 0) {
			break;
		}

		sendToRoom(buf, nread);
	}

	close(fd);
	connectedClientSocket.remove(fd);

	printf("some one disconnect\n");

	return NULL;
}

void sendToRoom(char *buf, int nread) 
{
	printf("<> message: %s\n", buf); // вывод на сервере

	connectedClientSocket.for_each(SendWrapper);
}

void SendWrapper (int number) 
{
	char buf[256];
	send(number, buf, 0, 0);
}