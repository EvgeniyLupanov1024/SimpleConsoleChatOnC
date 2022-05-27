#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/types.h>        
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdbool.h>
#include <string.h>

#include "socket_error_proxy.c"
#include "STL/forward_list_int.c"

void * waitNewClientConect();
void * forwardingWithClient(void *arg);
void sendToRoom(char *buf, int nread);

int serverSocket;
struct sockaddr_in addr;
socklen_t addrlen;

#define int ConnectCount = 5;
forward_list_int connectedClientSocket;
connectedClientSocket = forward_list_int_init();

int main()
{
	serverSocket = Socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM -- TSP

	addr.sin_family = AF_INET; // семейство адресов для IPv4
	addr.sin_port = htons(8011); // порт, который будет слушать сервер
	addrlen = sizeof addr;

	Bind(serverSocket, (struct sockaddr *) &addr, sizeof addr);

	Listen(serverSocket, freeConnectCount);

	waitNewClientConect();

	close(serverSocket);
	return 0;
}

void * waitNewClientConect()
{
	while(true)
	{
		if (freeConnectCount < 1) {
			sleep(1);
		} else {
			break;
		}
	}

	freeConnectCount -= 1;
	int fd = Accept(serverSocket, (struct sockaddr *) &addr, &addrlen);
	connectedClientSocket[freeConnectCount] = fd;

	printf("some one connect\n");

	pthread_t thread;
	pthread_create(&thread, NULL, forwardingWithClient, &fd);

	return nullptr;
}

void * forwardingWithClient(void *arg)
{
	int fd = * (int *) arg;

	while(true)
	{
		char buf[256] {'\0'};
		recv(fd, buf, 256, 0); // вернёт ответ после изменения сокета; если соединение разорванно -- вернёт 0
		int nread = strlen(buf);

		if (nread == 0) {
			break;
		}

		printf("<> message: %s\n", buf); // вывод на сервере

		sendToRoom(buf, nread);
	}

	connectedClientSocket[freeConnectCount] = 0;
	close(fd);
	freeConnectCount += 1;

	printf("some one disconnect\n");

	return NULL;
}

void sendToRoom(char *buf, int nread) 
{
	for (size_t i = 0; i < 5; i++)
	{
		if (connectedClientSocket[i] == 0) {
			continue;
		}

		send(connectedClientSocket[i], buf, nread, 0);
	}
}
