PROGRAM=tree
OBJECTS=main.o bintree.o tree_printer.o string_worker.o
CFLAGS=-Wall -Wextra -Werror -O3 -g -std=gnu89
LDLIBS=
CC=gcc

all: main

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

bintree.o: bintree.c
	$(CC) -o bintree.o -c bintree.c $(CFLAGS)

tree_printer.o: tree_printer.c bintree.o
	$(CC) -o tree_printer.o -c tree_printer.c $(CFLAGS)

string_worker.o: string_worker.c
	$(CC) -o string_worker.o -c string_worker.c $(CFLAGS)

main: main.o tree_printer.o bintree.o string_worker.o
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

run: main
	./$(PROGRAM)

clear:
	rm $(PROGRAM) $(OBJECTS)