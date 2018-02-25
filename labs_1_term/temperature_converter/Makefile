PROGRAM=tconvert
OBJECTS=main.o
CFLAGS=-Wall -Wextra -Werror -std=gnu89
CC=gcc

.PHONY: all clean

all: tconvert

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

tconvert: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(PROGRAM)
