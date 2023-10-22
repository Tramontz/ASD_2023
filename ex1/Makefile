CC = gcc
all: bin/sorting_algo_tests bin/main_ex1
CFLAGS = -g -w -Wall -Wextra -Wpedantic -Wconversion
INCLUDES = src/*.h
BUILD_DIR= build/
BIN_DIR= bin/
COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

bin/sorting_algo_tests: build/sorting_algo.o  build/sorting_algo_tests.o build/unity.o $(BIN_DIR)
	$(CC) -o bin/sorting_algo_tests build/sorting_algo.o build/sorting_algo_tests.o build/unity.o 

bin/main_ex1: build/struct_array.o build/sorting_algo.o build/main_ex1.o $(BIN_DIR)
	$(CC) -o bin/main_ex1 build/struct_array.o build/sorting_algo.o build/main_ex1.o

clean:
	rm -f build/* bin/* 
	
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)