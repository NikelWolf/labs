PROGRAM=ls
OBJECTS=main.o
CFLAGS=-Wall -Wextra -std=gnu89
LDLIBS=
CC=gcc

all: main

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

main: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

clear:
	rm $(PROGRAM) *.o