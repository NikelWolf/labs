PROGRAM=http_server
PROGRAM_ARGUMENTS=configuration_template.ini
OBJECTS=main.o logger.o utils.o configs_parser.o string_worker.o server_utils.o
CFLAGS=-Wall -Werror -std=gnu89
LDLIBS=
CC=gcc

all: server

utils.o: utils.c
	$(CC) -o utils.o -c utils.c $(CFLAGS)

logger.o: utils.o logger.c
	$(CC) -o logger.o -c logger.c $(CFLAGS)

string_worker.o: string_worker.c
	$(CC) -o string_worker.o -c string_worker.c $(CFLAGS)

configs_parser.o: utils.o string_worker.o configs_parser.c
	$(CC) -o configs_parser.o -c configs_parser.c $(CFLAGS)

server_utils.o: logger.o configs_parser.o server_utils.c
	$(CC) -o server_utils.o -c server_utils.c $(CFLAGS)

main.o: configs_parser.o logger.o server_utils.o main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

server: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

clear:
	rm -r *.o $(PROGRAM)

run: all
	./$(PROGRAM) $(PROGRAM_ARGUMENTS)
