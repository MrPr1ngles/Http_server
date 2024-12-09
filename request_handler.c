#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include "request_handler.h"

void parse_request(const char *buffer, Request *request) {
    request->method = strtok((char *)buffer, " ");
    request->uri = strtok(NULL, " ");
    request->http_version = strtok(NULL, " ");
}

void handle_request(int socket) {
    char buffer[1024] = {0};
    Request request;
    char *file_path;
    int file_fd;
    struct stat file_stat;
    char response_header[1024];

    // Чтение запроса
    read(socket, buffer, 1024);
    printf("Request: %s\n", buffer);

    // Разбор запроса
    parse_request(buffer, &request);

    if (strcmp(request.method, "GET") != 0) {
        // Обработка только GET-запросов
        snprintf(response_header, sizeof(response_header),
                 "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 0\r\n\r\n");
        write(socket, response_header, strlen(response_header));
        return;
    }

    // Определение пути к файлу
    file_path = request.uri + 1; // Удаление начального слэша
    if (strlen(file_path) == 0) {
        file_path = "index.html";
    }

    // Открытие файла
    file_fd = open(file_path, O_RDONLY);
    if (file_fd == -1) {
        // Файл не найден
        snprintf(response_header, sizeof(response_header),
                 "HTTP/1.1 404 Not Found\r\nContent-Length: 21\r\n\r\n 404 not found");
        write(socket, response_header, strlen(response_header));
        return;
    }

    // Получение информации о файле
    if (fstat(file_fd, &file_stat) == -1) {
        close(file_fd);
        snprintf(response_header, sizeof(response_header),
                 "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n");
        write(socket, response_header, strlen(response_header));
        return;
    }

    // Формирование заголовка ответа
    snprintf(response_header, sizeof(response_header),
             "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", file_stat.st_size);
    write(socket, response_header, strlen(response_header));

    // Отправка файла
    sendfile(socket, file_fd, NULL, file_stat.st_size);

    // Закрытие файла
    close(file_fd);
}
