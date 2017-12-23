PROGRAM=tconvert
OBJECTS=main.o
CFLAGS=-Wall -Wextra -Werror -g -O3 -std=gnu89
LDLIBS=
CC=gcc

all: tconvert

main.o: main.c 
	$(CC) -c main.c -o main.o $(CFLAGS)

tconvert: main.o
	$(CC) -o $(PROGRAM) $(LDLIBS) $(OBJECTS)

clear:
	rm *.o tconvert