PROGRAM=calc
OBJECTS=main.o stack.o utils.o
CFALGS=-Wall -Wextra -Werror -std=gnu89
CC=gcc

.PHONY: all clean

all: main

stack.o: stack.c stack.h
	$(CC) -o stack.o -c stack.c $(CFALGS)

utils.o: utils.c utils.h
	$(CC) -o utils.o -c utils.c $(CFALGS)

main.o: stack.o utils.o
	$(CC) -o main.o -c main.c $(CFALGS)

main: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(PROGRAM)
