#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>

typedef struct {
    int port;
    int server_fd;
    struct sockaddr_in address;
} Server;

void start_server(Server *server);

#endif
