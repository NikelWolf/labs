PROGRAM=http_server
OBJECTS=main.o logger.o utils.o configs_parser.o string_worker.o server_utils.o
CFLAGS=-Wall -Wextra -Werror -std=gnu89
CC=gcc

.PHONY: all clean

all: server

utils.o: utils.c utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

logger.o: logger.c logger.h utils.o
	$(CC) -o logger.o -c logger.c $(CFLAGS)

string_worker.o: string_worker.c string_worker.h
	$(CC) -o string_worker.o -c string_worker.c $(CFLAGS)

configs_parser.o: configs_parser.c configs_parser.h utils.o string_worker.o
	$(CC) -o configs_parser.o -c configs_parser.c $(CFLAGS)

server_utils.o: server_utils.c server_utils.h logger.o configs_parser.o
	$(CC) -o server_utils.o -c server_utils.c $(CFLAGS)

main.o: configs_parser.o logger.o server_utils.o main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

server: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(PROGRAM)
