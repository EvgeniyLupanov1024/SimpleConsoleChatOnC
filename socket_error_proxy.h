#ifndef SOCKET_ERROR_PROXY_H
#define SOCKET_ERROR_PROXY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/socket.h>

int Socket(int domain, int type, int protocol);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Inet_pton(int af, const char *src, void *dist);

int Send (int sockfd, const char *buf, int len, int flags);

#endif
