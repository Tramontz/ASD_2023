#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"

int compare_int(const void *a, const void *b) {
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

int main() {
    srand((unsigned)time(NULL));
 
    SkipList *int_list;
    new_skiplist(&int_list, 10, compare_int);

    int int_keys[] = {3, 6, 1, 8, 2, 7, 5, 4, 9};

    printf("Inserimento nella SkipList con interi: %d \n",sizeof(int_keys) / sizeof(int_keys[0]));
    for (size_t i = 0; i < sizeof(int_keys) / sizeof(int_keys[0]); i++) {
      printf("Inserimento %d\n: ", int_keys[i]);
        insert_skiplist(int_list, int_keys[i]);
        //print_skiplist(int_list, 0); // Pass 0 for integers
    }
    clear_skiplist(int_list);

    /*SkipList *str_list;
    new_skiplist(&str_list, 10, compare_string);

    char *str_keys[] = {"apple", "banana", "cherry", "date", "fig", "grape", "kiwi"};

    printf("\nInserimento nella SkipList con stringhe:\n");
    for (size_t i = 0; i < sizeof(str_keys) / sizeof(str_keys[0]); i++) {
        insert_skiplist(str_list, str_keys[i]);
        printf("Inserimento %s: ", str_keys[i]);
        print_skiplist(str_list, 1); // Pass 1 for strings
    }

    clear_skiplist(&str_list);
*/
    return 0;
}