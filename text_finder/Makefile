PROGRAM=text_finder
OBJECTS=main.o
CFLAGS=-Wall -Wextra -Werror -O3 -g -std=gnu89
LDLIBS=
CC=gcc

all: main

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

main: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

clear:
	rm $(PROGRAM) $(OBJECTS)