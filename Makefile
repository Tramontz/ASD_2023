CC = gcc
all: bin/sorting_algo_tests bin/sorting_algo_main_ex

CFLAGS = -g -w -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/sorting_algo_tests: build/sorting_algo.o  build/sorting_algo_tests.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/sorting_algo_tests build/sorting_algo.o build/sorting_algo_tests.o build/unity.o 

bin/sorting_algo_main_ex: build/struct_array.o build/sorting_algo.o build/sorting_algo_main_ex.o $(COMMON_DEPS)
	$(CC) -o bin/sorting_algo_main_ex build/struct_array.o build/sorting_algo.o build/sorting_algo_main_ex.o

clean:
	rm -f build/* bin/* 
	