    ///Общее строение HTTP-сервера///

Сетевой интерфейс:
  HTTP-сервер слушает определенный порт (обычно 80 для HTTP) и принимает входящие соединения от клиентов.

Обработка запросов:
  После установления соединения сервер читает HTTP-запрос от клиента.
  Запрос содержит метод (GET, POST, PUT, DELETE и т.д.), URI (Uniform Resource Identifier), версию HTTP и заголовки.

Обработка URI:
  Сервер анализирует URI, чтобы определить, какой ресурс запрашивается.
  URI может указывать на статический файл (например, HTML, CSS, JavaScript, изображения) или динамический ресурс (например, скрипт на сервере).

Генерация ответа:
  Сервер формирует HTTP-ответ, который включает статусный код, заголовки и тело ответа.
  Статусный код указывает результат обработки запроса (например, 200 OK, 404 Not Found, 500 Internal Server Error).

Отправка ответа:
  Сервер отправляет сформированный ответ обратно клиенту через установленное соединение.

Закрытие соединения:
  После отправки ответа сервер может закрыть соединение или оставить его открытым для последующих запросов (в зависимости от настроек и версии HTTP).
_____________________________________________________________________________________

Основные статусные коды HTTP:
  200 OK: Запрос успешно обработан.
  400 Bad Request: Запрос имеет неверный синтаксис.
  401 Unauthorized: Требуется аутентификация.
  403 Forbidden: Доступ запрещен.
  404 Not Found: Запрашиваемый ресурс не найден.
  500 Internal Server Error: Внутренняя ошибка сервера.
  503 Service Unavailable: Сервер временно недоступен.
_____________________________________________________________________________________


    ///Разбор кода///
MAIN
1. Подключение заголовочных файлов
  #include <stdio.h>: Подключает стандартную библиотеку ввода-вывода. Это позволяет использовать функции для вывода информации на экран, такие как printf.
  #include "server.h": Подключает заголовочный файл server.h, который содержит определение структуры Server и прототип функции start_server. Это необходимо для использования этих компонентов в main.c.
2. main
  Установка порта сервера:
    server.port = 8080;: Устанавливается порт сервера на 8080. Это означает, что сервер будет слушать входящие соединения на порту 8080.
  Запуск сервера:
    start_server(&server);: Вызывается функция start_server, которая принимает указатель на структуру Server. Эта функция отвечает за создание и запуск сервера.

  Возврат из функции main:
    return 0;: Функция main возвращает 0, что означает успешное завершение программы.

    

SERVER
1. Подключение заголовочных файлов   
    #include <stdio.h>: Подключает стандартную библиотеку ввода-вывода для функций, таких как printf и perror.
    #include <stdlib.h>: Подключает стандартную библиотеку для работы с памятью и управления процессами, такими как exit.
    #include <string.h>: Подключает стандартную библиотеку для работы со строками, такими как memset.
    #include <unistd.h>: Подключает стандартную библиотеку для работы с POSIX API, такими как close.
    #include <arpa/inet.h>: Подключает библиотеку для работы с интернет-адресами и функциями, такими как htons.
    #include "server.h": Подключает заголовочный файл server.h, который содержит определение структуры Server и прототип функции start_server.
    #include "request_handler.h": Подключает заголовочный файл request_handler.h, который содержит прототип функции handle_request.
2. Функция start_server
    Объявление переменных:
        int opt = 1;: Переменная для настройки опций сокета.
        int addrlen = sizeof(server->address);: Переменная для хранения длины адреса.
        int new_socket;: Переменная для хранения дескриптора нового сокета.
3. Создание сокета    
    Создание сокета:
        socket(AF_INET, SOCK_STREAM, 0): Создает новый сокет для IPv4 и TCP.
        Проверяется успешность создания сокета. Если сокет не был создан, выводится сообщение об ошибке и программа завершается с кодом ошибки.
4. Настройка сокета
    Настройка сокета:
        setsockopt: Устанавливает опции сокета для повторного использования адреса и порта.
        Проверяется успешность установки опций. Если опции не были установлены, выводится сообщение об ошибке и программа завершается с кодом ошибки.
5. Привязка сокета к адресу и порту
    Заполнение структуры адреса:
        server->address.sin_family = AF_INET;: Устанавливает семейство адресов на IPv4.
        server->address.sin_addr.s_addr = INADDR_ANY;: Устанавливает адрес на любой доступный интерфейс.
        server->address.sin_port = htons(server->port);: Устанавливает порт сервера, преобразуя его в сетевой порядок байтов.
    Привязка сокета:
        bind: Привязывает сокет к указанному адресу и порту.
        Проверяется успешность привязки. Если привязка не удалась, выводится сообщение об ошибке и программа завершается с кодом ошибки.
6. Прослушивание входящих соединений
     Прослушивание соединений:
        listen: Переводит сокет в режим прослушивания, устанавливая максимальное количество ожидающих соединений на 3.
        Проверяется успешность перехода в режим прослушивания. Если прослушивание не удалось, выводится сообщение об ошибке и программа завершается с кодом ошибки
7. Основной цикл сервера
    Вывод сообщения о запуске сервера:
        printf("Server is running on port %d\n", server->port);: Выводит сообщение о том, что сервер запущен и слушает на указанном порту.
    Бесконечный цикл:
        while (1): Бесконечный цикл, который позволяет серверу постоянно принимать новые соединения.
    Принятие входящего соединения:
        accept: Принимает входящее соединение и возвращает новый дескриптор сокета.
        Проверяется успешность принятия соединения. Если соединение не было принято, выводится сообщение об ошибке и программа завершается с кодом ошибки.
    Обработка запроса:
        handle_request(new_socket);: Вызывает функцию handle_request, которая принимает дескриптор нового сокета и отвечает за обработку HTTP-запроса.
    Закрытие сокета:
        close(new_socket);: Закрывает сокет после обработки запроса.


REQUEST_HANDLER
1. Функция parse_request
    Объявление функции parse_request:
        void parse_request(const char *buffer, Request *request): Функция принимает строку запроса и указатель на структуру Request.
    Разбор строки запроса:
        strtok((char *)buffer, " "): Разбивает строку запроса на токены, используя пробел в качестве разделителя. Первый токен — это метод запроса (например, GET).
        strtok(NULL, " "): Продолжает разбивать строку запроса. Второй токен — это URI (например, /index.html).
        strtok(NULL, " "): Продолжает разбивать строку запроса. Третий токен — это версия HTTP (например, HTTP/1.1).
2. Функция handle_request    
    Объявление переменных:
        char buffer[1024] = {0};: Буфер для чтения запроса.
        Request request;: Структура для хранения информации о запросе.
        char *file_path;: Указатель на строку, содержащую путь к файлу.
        int file_fd;: Дескриптор файла.
        struct stat file_stat;: Структура для хранения информации о файле.
        char response_header[1024];: Буфер для формирования заголовка ответа.
3.Чтение запроса
    Чтение данных из сокета:
        read(socket, buffer, 1024);: Читает данные из сокета в буфер.
        printf("Request: %s\n", buffer);: Выводит содержимое буфера на экран для отладки.
4. Разбор запроса
    Вызов функции parse_request:
        parse_request(buffer, &request);: Разбирает строку запроса и заполняет структуру Request.
5.Проверка метода зароса
   Проверка метода запроса:
        strcmp(request.method, "GET") != 0: Проверяет, является ли метод запроса GET.
        Если метод не GET, формируется ответ с кодом 405 (Method Not Allowed) и отправляется клиенту.
6. Определение пути к файлу   
    Определение пути к файлу:
        file_path = request.uri + 1;: Удаляет начальный слэш из URI.
        if (strlen(file_path) == 0): Если URI пустой, устанавливает путь к файлу index.html.
7. Открытие файла
    Открытие файла:
        open(file_path, O_RDONLY);: Открывает файл для чтения.
        Проверяется успешность открытия файла. Если файл не найден, формируется ответ с кодом 404 (Not Found) и отправляется клиенту.
8. Получение информации о файле
    Получение информации о файле:
        fstat(file_fd, &file_stat);: Получает информацию о файле.
        Проверяется успешность получения информации. Если произошла ошибка, формируется ответ с кодом 500 (Internal Server Error) и отправляется клиенту.
9. Формирование заголовка ответа
   Формирование заголовка ответа:
        snprintf(response_header, sizeof(response_header), "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", file_stat.st_size);: Формирует заголовок ответа с кодом 200 (OK) и длиной файла.
        write(socket, response_header, strlen(response_header));: Отправляет заголовок ответа клиенту.
10. Отправка файла
    Отправка файла:
        sendfile(socket, file_fd, NULL, file_stat.st_size);: Отправляет содержимое файла клиенту.
11. Закрытие файла
    Закрытие файла:
        close(file_fd);: Закрывает файл

