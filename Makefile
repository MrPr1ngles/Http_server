


start: main.o request_handler.o server.o
	gcc -o start main.o request_handler.o server.o 

main.o: main.c
	gcc -c main.c 

request.o: request_handler.C
	gcc -c request_handler.c

server.o: server.c 
	gcc -c server.c

