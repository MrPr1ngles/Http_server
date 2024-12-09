#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

typedef struct {
    char *method;
    char *uri;
    char *http_version;
} Request;

void handle_request(int socket);

#endif
