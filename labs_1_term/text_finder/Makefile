PROGRAM=text_finder
OBJECTS=main.o
CFLAGS=-Wall -Wextra -Werror -std=gnu89
CC=gcc

.PHONY: all clean

all: main

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

main: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS)

clean:
	$(RM) $(PROGRAM) $(OBJECTS)
