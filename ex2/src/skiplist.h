#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stddef.h>

typedef struct _Node Node;
typedef struct _SkipList SkipList;

// Alloca una nuova SkipList vuota
void new_skiplist(SkipList **list, size_t max_height, int (*compare)(const void *, const void *));

// Dealloca una SkipList e tutti i suoi nodi
void clear_skiplist(SkipList **list);

// Inserisce un elemento nella SkipList
void insert_skiplist(SkipList *list, void *item);

// Verifica se un elemento è presente nella SkipList
const void *search_skiplist(SkipList *list, void *item);

// Funzione per visualizzare la SkipList
void print_skiplist(SkipList *list, int is_string);

#endif
