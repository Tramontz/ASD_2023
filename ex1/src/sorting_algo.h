#ifndef SORTING_ALGO_H_ispuniproject
#define SORTING_ALGO_H_ispuniproject

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


void merge_binary_insertion_sort(void **base, size_t nitems, size_t k, int (*comparator)(const void*, const void*));

#endif /* SORTING_ALGO_H_ispuniproject */