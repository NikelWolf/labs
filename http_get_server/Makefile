PROGRAM=http_server
PROGRAM_ARGUMENTS=configuration.ini
OBJECTS_DIR=objects
HEADERS_DIR=headers
SOURCES_DIR=sources
BIN_DIR=bin
OBJECTS={main.o,logger.o,utils.o,configs_parser.o,string_worker.o,http_helper.o,inet_utils.o,server_utils.o}
CFLAGS=-I$(HEADERS_DIR) -Wall -Werror -g -O0 -std=gnu89
LDLIBS=
CC=gcc

all: init_dirs server

init_bin_dir:
	if [ ! -d ./$(BIN_DIR) ]; then mkdir $(BIN_DIR); fi

init_obj_dir:
	if [ ! -d ./$(OBJECTS_DIR) ]; then mkdir $(OBJECTS_DIR); fi;

init_dirs: init_obj_dir init_bin_dir

utils.o: $(SOURCES_DIR)/utils.c
	$(CC) -o $(OBJECTS_DIR)/utils.o -c $(SOURCES_DIR)/utils.c $(CFLAGS)

logger.o: utils.o $(SOURCES_DIR)/logger.c
	$(CC) -o $(OBJECTS_DIR)/logger.o -c $(SOURCES_DIR)/logger.c $(CFLAGS)

string_worker.o: $(SOURCES_DIR)/string_worker.c
	$(CC) -o $(OBJECTS_DIR)/string_worker.o -c $(SOURCES_DIR)/string_worker.c $(CFLAGS)

configs_parser.o: utils.o string_worker.o $(SOURCES_DIR)/configs_parser.c
	$(CC) -o $(OBJECTS_DIR)/configs_parser.o -c $(SOURCES_DIR)/configs_parser.c $(CFLAGS)

http_helper.o: string_worker.o configs_parser.o $(SOURCES_DIR)/http_helper.c
	$(CC) -o $(OBJECTS_DIR)/http_helper.o -c $(SOURCES_DIR)/http_helper.c $(CFLAGS)

inet_utils.o: $(SOURCES_DIR)/inet_utils.c
	$(CC) -o $(OBJECTS_DIR)/inet_utils.o -c $(SOURCES_DIR)/inet_utils.c $(CFLAGS)

server_utils.o: $(SOURCES_DIR)/server_utils.c
	$(CC) -o $(OBJECTS_DIR)/server_utils.o -c $(SOURCES_DIR)/server_utils.c $(CFLAGS)

main.o: configs_parser.o logger.o http_helper.o server_utils.o inet_utils.o $(SOURCES_DIR)/main.c
	$(CC) -o $(OBJECTS_DIR)/main.o -c $(SOURCES_DIR)/main.c $(CFLAGS)

server: main.o
	$(CC) -o $(BIN_DIR)/$(PROGRAM) $(OBJECTS_DIR)/$(OBJECTS) $(LDLIBS)

clear:
	rm -rf $(OBJECTS_DIR) $(BIN_DIR)

run: all
	$(BIN_DIR)/$(PROGRAM) $(PROGRAM_ARGUMENTS)

leak_check: all
	valgrind --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$(PROGRAM) $(PROGRAM_ARGUMENTS)