PROGRAM=calendar
OBJECTS=main.o
CFLAGS=-Wall -Wextra -Werror -std=gnu89
CC=gcc

.PHONY: all clean

all: main

main: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS)

main.o: main.c
	$(CC) -c main.c $(CFALGS)

clean:
	$(RM) $(PROGRAM) $(OBJECTS)
