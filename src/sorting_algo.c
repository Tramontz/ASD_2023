#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting_algo.h"

// Example print function for strings
void print_string_element(void *elem) {
    int **x = (int **)elem;
    printf("%d", *x);
}

void print_element(void *elem) {
    print_string_element(elem);
}

int binary_search(void *arr, void *item, int low, int high, CompareFunction compare, size_t elementSize) {
    if (high <= low){
        printf("DEBUG: arr: %p, low: %d, elementSize: %zu\n", arr, low, elementSize);
        printf("DEBUG: item: %p\n", item);
        return (compare(item, arr + low * elementSize) > 0) ? (low + 1) : low ;
    }

    int mid = (low + high) / 2;

    int cmpResult = compare(item, arr + mid * elementSize);
    if (cmpResult == 0)
        return mid + 1;
    if (cmpResult > 0)
        return binary_search(arr, item, mid + 1, high, compare, elementSize);
    return binary_search(arr, item, low, mid - 1, compare, elementSize);
}

void bin_insertion_sort(void *arr, int n, size_t elementSize, CompareFunction compare) {
    int i, loc, j;
    void *selected = malloc(elementSize);
    if (selected == NULL) {
        fprintf(stderr, "Errore nell'allocazione di memoria per 'selected'\n");
        exit(EXIT_FAILURE);
    }
    printf("Valore di n: %d\n", n);
    for (i = 1; i < n; ++i) {
        j = i - 1;
        memcpy(selected, arr + i * elementSize, elementSize);
            // Find location where selected should be inserted
        loc = binary_search(arr, selected, 0, j, compare, elementSize);
            // Move all elements after location to create space
        while (j >= loc) {
            memcpy(arr + (j + 1) * elementSize, arr + j * elementSize, elementSize);
            j--;
        }
        memcpy(arr + (j + 1) * elementSize, selected, elementSize);
    }
    free(selected);
}

void merge(void *arr, int left, int mid, int right, size_t elementSize, CompareFunction compare) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

        // Create temporary arrays for the left and right subarrays
    void *L = malloc(n1 * elementSize);
    void *R = malloc(n2 * elementSize);

        // Copy data from the original array to the temporary arrays
    memcpy(L, arr + (left * elementSize), n1 * elementSize);
    memcpy(R, arr + ((mid + 1) * elementSize), n2 * elementSize);

        // Merge the temporary arrays back into the original array
        i = 0; // Initial index of left subarray
        j = 0; // Initial index of right subarray
        k = left; // Initial index of merged subarray

        while (i < n1 && j < n2) {
            void *leftElem = L + (i * elementSize);
            void *rightElem = R + (j * elementSize);

            if (compare(leftElem, rightElem) <= 0) {
                // If left element <= right element, copy the left element to the merged subarray
                memcpy(arr + (k * elementSize), leftElem, elementSize);
                i++;
            } else {
                // If left element > right element, copy the right element to the merged subarray
                memcpy(arr + (k * elementSize), rightElem, elementSize);
                j++;
            }
            k++;
        }

        // Copy any remaining elements from the left subarray
        while (i < n1) {
            memcpy(arr + (k * elementSize), L + (i * elementSize), elementSize);
            i++;
            k++;
        }

        // Copy any remaining elements from the right subarray
        while (j < n2) {
            memcpy(arr + (k * elementSize), R + (j * elementSize), elementSize);
            j++;
            k++;
        }

        // Free the temporary arrays
        free(L);
        free(R);
    }

    void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, CompareFunction compare){
        if(base == NULL){
            fprintf(stderr,"the given array cannot be null");
            exit(EXIT_FAILURE);
        }
        else merge_binary_insertion_sort_rec(base, 0, nitems-1, k, size, compare);
    }

    void merge_binary_insertion_sort_rec(void *arr, int left, int right, size_t k, size_t elementSize, CompareFunction compare) {

        printf("%d,%d,%d,%d\n", left,right,k,elementSize);
        if (left < right) {
            if (right - left + 1 <= k) {
                // Use bin_insertion_sort for small subarrays
                bin_insertion_sort(arr + (left * elementSize), right - left + 1, elementSize, compare);
            } else {
                int mid = left + (right - left) / 2;

                // Sort the left and right halves recursively
                merge_binary_insertion_sort_rec(arr, left, mid, k, elementSize, compare);
                merge_binary_insertion_sort_rec(arr, mid + 1, right, k, elementSize, compare);

                // Merge the sorted halves
                merge(arr, left, mid, right, elementSize, compare);
            }
        }
    }