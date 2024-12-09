#include <stdio.h>
#include "server.h"

int main() {
    Server server;
    server.port = 8080;
    start_server(&server);
    return 0;
}
