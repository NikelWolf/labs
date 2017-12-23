PROGRAM=calc
OBJECTS=main.o stack.o utils.o
CFALGS=-Wall -Wextra -Werror -g -O3 -std=gnu89
LDLIBS=
CC=gcc

all: main

stack.o:
	$(CC) -o stack.o -c stack.c $(CFALGS)

utils.o:
	$(CC) -o utils.o -c utils.c $(CFALGS)

main.o: stack.o utils.o
	$(CC) -o main.o -c main.c $(CFALGS)

main: main.o
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

clear: 
	rm *.o $(PROGRAM)