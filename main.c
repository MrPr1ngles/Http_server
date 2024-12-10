#include <stdio.h>
#include "server.h"

int main() {
    Server server;
    printf("Введите порт \n");
    scanf("%d", &server.port);
    start_server(&server);
    return 0;
}
