#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

int main(int argc, char *argv[]) {
    int port = 0;
    int opt;

    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                port = atoi(optarg);
                if (port <= 0 || port > 99999) {
                    printf( "Invalid port number: %s\n", optarg);
                    return 1;
                }
                break;
            default:
                printf( "Usage: %s -p <port>\n", argv[0]);
                return 1;
        }
    }

    if (port == 0) {
        printf("Port number is required. Usage: %s -p <port>\n", argv[0]);
        return 1;
    }

    Server server;
    server.port = port;
    start_server(&server);
    return 0;
}
