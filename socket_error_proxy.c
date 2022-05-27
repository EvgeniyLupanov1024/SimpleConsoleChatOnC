#include "headers/socket_error_proxy.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int Socket(int domain, int type, int protocol)
{
	int result = socket(domain, type, protocol);	
	if (result == -1) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	return result;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int result = bind(sockfd, addr, addrlen);
	if (result == -1) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	return result;
}

int Listen(int sockfd, int backlog)
{
	int result = listen(sockfd, backlog);
	if (result == -1) {
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	return result;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int result = accept(sockfd, addr, addrlen);
	if (result == -1) {
		perror("accept failed");
		exit(EXIT_FAILURE);
	}

	return result;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int result = connect(sockfd, addr, addrlen);
	if (result == -1) {
		perror("accept failed");
		exit(EXIT_FAILURE);
	}

	return result;
}

int Inet_pton(int af, const char *src, void *dist)
{
	int result = inet_pton(af, src, dist);

	if (result == 0) {
		perror("inet_pton failed: src does not contain character\n");
		exit(EXIT_FAILURE);
	}
	else if (result == -1) {
		perror("inet_pton failed");
		exit(EXIT_FAILURE);
	}

	return result;
}
