PROGRAM=calendar
OBJECTS=main.o
CFLAGS=-Wall -Wextra -Werror -std=gnu89
CC=gcc

.PHONY: all clean

all: main

main: main.o
	gcc -c main.c $(CFALGS)

main.o: main.c
	gcc -o $(PROGRAM) $(OBJECTS)

clean:
	$(RM) $(PROGRAM) $(OBJECTS)
