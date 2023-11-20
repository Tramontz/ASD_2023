#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skiplist.h"
#include "unity.h"

// Comparison function for interi
int compare_int(const void *a, const void *b) {
    int x = (int *)a;
    int y = (int *)b;
    return (x - y);
}

// Comparison function for stringhe
int compare_string(const void *a, const void *b) {
    char **x = (char **)a;
    char **y = (char **)b;
    return strcmp(x, y);
}

void testEmptySkipList() {
    printf("1ui 1\n");
    SkipList *list;
    printf("1ui 2\n");

    new_skiplist(&list, 10, compare_int);
    TEST_ASSERT_NULL(search_skiplist(list, 42));
    clear_skiplist(&list);
}

void testSkipListWithSingleElement() {
    SkipList *list;
    new_skiplist(&list, 10, compare_int);
    int value = 42;
    insert_skiplist(list, value);
    const void *result = search_skiplist(list, value);
    TEST_ASSERT_EQUAL_PTR(value, result);
    clear_skiplist(&list);
}

void testSkipListWithIntElements() {
    SkipList *list;
    new_skiplist(&list, 10, compare_int);

    for (int i = 1; i <= 50; i++) {
        insert_skiplist(list, i);
    }

    int value = 42;
    const void *result = search_skiplist(list, value);
    TEST_ASSERT_EQUAL_PTR(value, result);

    clear_skiplist(&list);
}

void testSkipListWithStringElements() {
    SkipList *list;
    new_skiplist(&list, 10, compare_string);

    char *words[] = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon",
    "mango", "nectarine", "orange", "pear", "quince", "raspberry", "strawberry", "tangerine", "uriku",
    "vitis", "watermelon", "xigua", "yuzu", "zucchini", "apricot", "blueberry", "cranberry", "dragonfruit",
    "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon", "mango", "nectarine", "orange", "pear",
    "quince", "raspberry", "strawberry", "tangerine", "uriku", "vitis", "watermelon", "xigua", "yuzu",
    "zucchini"};

    for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++) {
        insert_skiplist(list, words[i]);
    }print_skiplist(&list, 1);

    const char *searchWord = "fig";
    const void *result = search_skiplist(list, searchWord);
    TEST_ASSERT_EQUAL_STRING(searchWord, (const char *)result);

    clear_skiplist(&list);
}

int main() {
    UNITY_BEGIN();

    //RUN_TEST(testEmptySkipList);
    //RUN_TEST(testSkipListWithSingleElement);
    //RUN_TEST(testSkipListWithIntElements);
    RUN_TEST(testSkipListWithStringElements);

    UNITY_END();
}