PROGRAM=t4-dsa-p3-v6
OBJECTS=*.kt
CFLAGS=-include-runtime -d
CC=kotlinc

.PHONY: all clean

all: run

main:
	$(CC) $(OBJECTS) $(CFLAGS) $(PROGRAM).jar

run: main
	java -jar $(PROGRAM).jar

clean:
	$(RM) $(PROGRAM).jar
