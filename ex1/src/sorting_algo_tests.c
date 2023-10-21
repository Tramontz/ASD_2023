#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "sorting_algo.h"
    #include "unity.h"

    #define K_VALUE 5

    // Comparison function for integers

int compare_integers(const void *a, const void *b) {
    int x = (int *)a;
    int y = (int *)b;
    return (x - y);
}

    // Comparison function for strings
int compare_strings(const void *a, const void *b) {
    char **x = (char **)a;
    char **y = (char **)b;
    return strcmp(x, y);
}


    //Testing merge_binary_insertion_sort

void test_merge_single_element_int_array() {
    int singleArr[] = {5};
    int singleArrExpected[] = {5};

    merge_binary_insertion_sort(singleArr, 1, K_VALUE, compare_integers);

    TEST_ASSERT_EQUAL_INT_ARRAY(singleArrExpected, singleArr, 1);
}

void test_merge_equal_int_array() {
    int equalArr[] = {2, 2, 2, 2, 2};
    int equalArrExpected[] = {2, 2, 2, 2, 2};

    merge_binary_insertion_sort(equalArr, 5, K_VALUE, compare_integers);
    TEST_ASSERT_EQUAL_INT_ARRAY(equalArrExpected, equalArr, 5);
}

void test_mergee_gneric_int_array() {
    int genericArr[] = {50, 25, 10, 35, 40, 30, 20, 15, 5, 45, 1, 3, 48, 32, 18, 27, 8, 38, 23, 12,
    42, 47, 6, 33, 16, 43, 9, 28, 37, 22, 14, 36, 11, 19, 26, 49, 4, 21, 39,
    2, 46, 7, 29, 44, 17, 34, 13, 41, 31, 24};
    int genericArrExpected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
    37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

    merge_binary_insertion_sort(genericArr, 50, K_VALUE, compare_integers);


    TEST_ASSERT_EQUAL_INT_ARRAY(genericArrExpected, genericArr, 50);
}

void test_merge_string_array() {
    char* stringArr[] = {"hello", "world", "sorting", "algorithm", "test",
    "merge", "insertion", "sort", "example", "array",
    "function", "generic", "element", "comparison", "unity",
    "programming", "language", "computer", "science", "openai",
    "algorithm", "coding", "practice", "development", "software",
    "engineering", "knowledge", "solution", "challenge", "efficiency"};
    char* stringArrExpected[] = {"algorithm", "algorithm", "array", "challenge", "coding",
    "comparison", "computer", "development", "efficiency", "element",
    "engineering", "example", "function", "generic", "hello", "insertion",
    "knowledge", "language", "merge", "openai", "practice", "programming",
    "science", "software", "solution", "sort", "sorting", "test", "unity",
    "world"};

    merge_binary_insertion_sort(stringArr, 30,  K_VALUE, compare_strings);
    TEST_ASSERT_EQUAL_STRING_ARRAY(stringArrExpected, stringArr, 30);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_merge_single_element_int_array);
    RUN_TEST(test_merge_equal_int_array);
    RUN_TEST(test_mergee_gneric_int_array);
    RUN_TEST(test_merge_string_array);

    UNITY_END();
}
