#ifndef SOCKET_ERROR_PROXY_H
#define SOCKET_ERROR_PROXY_H

#include <sys/types.h> 
#include <sys/socket.h>

int Socket(int domain, int type, int protocol);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

#endif
