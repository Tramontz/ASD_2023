CC = gcc
all: bin/test_skiplist bin/main_ex2
CFLAGS = -g -w -Wall -Wextra -Wpedantic -Wconversion
INCLUDES = src/*.h
BUILD_DIR= build/
BIN_DIR= bin/
COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

bin/test_skiplist: build/skiplist.o  build/test_skiplist.o build/unity.o $(BIN_DIR)
	$(CC) -o bin/test_skiplist build/skiplist.o build/test_skiplist.o build/unity.o 

bin/main_ex2: build/skiplist.o build/main_ex2.o $(BIN_DIR)
	$(CC) -o bin/main_ex2 build/skiplist.o build/main_ex2.o

clean:
	rm -f build/* bin/* 
	
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)