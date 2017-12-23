PROGRAM=matrix_calc
OBJECTS=main.o string_worker.o matrix.o
CFALGS=-Wall -Wextra -Werror -g -O3 -std=gnu89
LDLIBS=
CC=gcc

all: main

string_worker.o: string_worker.c
	$(CC) -o string_worker.o -c string_worker.c $(CFALGS)

matrix.o: matrix.c string_worker.o
	$(CC) -o matrix.o -c matrix.c $(CFALGS)

main.o: main.c matrix.o string_worker.o
	$(CC) -o main.o -c main.c $(CFALGS)

main: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

run: all
	./$(PROGRAM)

clear: all
	rm *.o $(PROGRAM)