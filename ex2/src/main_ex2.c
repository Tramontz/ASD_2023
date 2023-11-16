#include "skiplist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare_int(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    return (x - y);
}

    // Comparison function for strings
int compare_strings(const void *a, const void *b) {
    char **x = (char **)a;
    char **y = (char **)b;
    return strcmp(x, y);
}

  
void print_skiplist(SkipList **list) {
    if (!*list) {
        printf("La SkipList è vuota.\n");
        return;
    }

    printf("SkipList:\n");

    for (size_t level = (*list)->max_height; level > 0; level--) {
        printf("Livello %lu: ", level);

        Node *current = (*list)->heads[level - 1];

        while (current) {
            printf("%d [", *((int *)current->item));

            // Print all levels of the current node
            for (size_t i = 0; i < current->size; i++) {
                printf("%lu ", i + 1);
            }

            printf("] ");
            current = current->next[0];
        }

        printf("\n");
    }
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
    }
print_skiplist(&int_list);
const void* found=search_skiplist(int_list,9);
    if(found!=NULL) printf("FOUNDED\n");
    clear_skiplist(&int_list);

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




