#include "sorting_algo.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#ifndef SWAP_DIMENSION
#define SWAP_DIMENSION 60
#endif

void merge_binary_insertion_sort(void **base, size_t nitems, size_t k, int (*comparator)(const void*, const void*)){
    if (base == NULL || comparator == NULL){
        printf("<a> and <comparator> cannot be NUll\n");
        return;
    }
    if (nitems < 0){
        printf("<start> and <end> cannot be negative\n");
        return;
    }
    merge_sort(base, 0, nitems - 1, k, comparator);
}

void insertion_sort(void **a, int start, int end, int (*comparator)(const void*, const void*)){

    int i, index, j;

    for (i = (start + 1); i <= end; ++i){

        j = i - 1;

        void *item = a[i];

        index = binary_search(a, item, start, j, comparator);

        while (j >= index){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = item;
    }
}

int binary_search(void **a, void *item, int left, int right, int (*comparator)(const void*, const void*)){
    if (right <= left)
        return ((comparator(item, a[left])) > 0) ? (left + 1) : left;

    int mid = (left + right) / 2;

    if (comparator(item, a[mid]) == 0)
        return mid + 1;

    if (comparator(item, a[mid]) > 0)
        return binary_search(a, item, mid + 1, right, comparator);

    return binary_search(a, item, left, mid - 1, comparator);
}

void merge_sort(void **a, int start, int end, size_t k, int (*comparator)(const void*, const void*)){
    if (start < end){
        if (end - start +1 <= k){  
            insertion_sort(a, start, end, comparator);
        }else{
            int middle_i = start + ((end - start) / 2);
            merge_sort(a, start, middle_i,k, comparator);
            merge_sort(a, middle_i + 1, end,k, comparator);
            merge(a, start, middle_i, end, comparator);
        }
    }
}

void merge(void **a, int start, int middle_i, int end, int (*comparator)(const void *, const void *)){
    int i, j, k;
    int n1 = middle_i - start + 1;
    int n2 = end - middle_i;
    void **left_half = (void **)calloc((size_t)n1, sizeof(void *));
    void **right_half = (void **)calloc((size_t)n2, sizeof(void *));
    for (i = 0; i < n1; i++)
        left_half[i] = a[start + i];
    for (j = 0; j < n2; j++)
        right_half[j] = a[middle_i + 1 + j];
    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2){
        if (comparator(left_half[i], right_half[j]) < 0 || comparator(left_half[i], right_half[j]) == 0){
            a[k] = left_half[i];
            i++;
        }else{
            a[k] = right_half[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        a[k] = left_half[i];
        i++;
        k++;
    }

    while (j < n2){
        a[k] = right_half[j];
        j++;
        k++;
    }

    free(left_half);
    free(right_half);
}