#ifndef SORTING_ALGO_H_ispuniproject
#define SORTING_ALGO_H_ispuniproject

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef int (*CompareFunction)(const void *, const void *);

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, CompareFunction compare);

#endif /* SORTING_ALGO_H_ispuniproject */