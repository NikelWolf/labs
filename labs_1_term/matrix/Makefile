PROGRAM=matrix_calc
OBJECTS=main.o string_worker.o matrix.o
CFALGS=-Wall -Wextra -Werror -std=gnu89
CC=gcc

.PHONY: all clean

all: main

string_worker.o: string_worker.c string_worker.h
	$(CC) -o string_worker.o -c string_worker.c $(CFALGS)

matrix.o: matrix.c matrix.h string_worker.o
	$(CC) -o matrix.o -c matrix.c $(CFALGS)

main.o: main.c matrix.o string_worker.o
	$(CC) -o main.o -c main.c $(CFALGS)

main: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS)

clean: all
	$(RM) $(OBJECTS) $(PROGRAM)
