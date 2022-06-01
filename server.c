#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <stdbool.h>
#include <string.h>

#include <sys/types.h>        
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket_proxy.h"
#include "list_int.h"

void init();

void waitNewClientConect();
void waitFreeSocket();
void * forwardingClient(void *arg);

bool SendCallback (list_int_node *node, void *arg);
void sendToRoom(char *buf);

int serverSocket;
struct sockaddr_in addr;
socklen_t addrlen;

const int maxConnectCount = 5;
const int bufferLen = 256;
list_int connectedClientSocket;

int main()
{
	init();

	serverSocket = Socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8011);
	addrlen = sizeof addr;

	Bind(serverSocket, (struct sockaddr *) &addr, sizeof addr);

	Listen(serverSocket, maxConnectCount);

	while(true)
	{
		waitNewClientConect();
	}

	close(serverSocket);
	return 0;
}

void init() 
{
	connectedClientSocket = list_int_init();
}

void waitNewClientConect()
{	
	waitFreeSocket();

	int fd = Accept(serverSocket, (struct sockaddr *) &addr, &addrlen);
	AddFirst(&connectedClientSocket, fd);
	printf("some one connect\n");

	pthread_t thread;
	pthread_create(&thread, NULL, forwardingClient, &fd);
}

void waitFreeSocket()
{
	while(true)
	{
		if (connectedClientSocket.count >= maxConnectCount) {
			sleep(1);
		} else {
			break;
		}
	}
}

void * forwardingClient(void *arg)
{
	int fd = * (int *) arg;
	char buf[bufferLen];
	int nread = bufferLen;

	while(true)
	{
		memset(buf, '\0', nread);

		nread = recv(fd, buf, bufferLen, 0);
		if (nread == 0) {
			printf("some one disconnect\n");
			break;
		}

		sendToRoom(buf);
	}

	close(fd);
	Remove(&connectedClientSocket, fd);

	return NULL;
}

void sendToRoom(char *buf) 
{
	printf("<> message: %s\n", buf);

	ForEach(&connectedClientSocket, SendCallback, buf);
}

bool SendCallback (list_int_node *node, void *arg) 
{
	char *buf = (char *) arg;

	Send(node->value, buf, strlen(buf), 0);

	return true;
}
