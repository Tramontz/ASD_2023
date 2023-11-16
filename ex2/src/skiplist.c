#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"

typedef struct _Node {
    Node **next;
    size_t size;    
    void *item;
} Node;

typedef struct _SkipList {
    Node **heads;
    size_t max_level;
    size_t max_height;
    int (*compare)(const void *, const void *);
} SkipList;


double random_probability() {
    return (double)rand() / RAND_MAX;
}

size_t random_level(size_t max_height) {
    size_t level = 1;
    while (random_probability() < 0.5 && level < max_height) {
        level++;
    }
    return level;
}

Node *create_node(void *item, size_t level) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Errore nell'allocazione del nodo.\n");
        exit(EXIT_FAILURE);
    }
    newNode->item = item;
    newNode->size = level;
    newNode->next = (Node **)malloc(level * sizeof(Node *));
    if (!newNode->next) {
        fprintf(stderr, "Errore nell'allocazione dei puntatori successivi.\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < level; i++) {
        newNode->next[i] = NULL;
    }

    return newNode;
}

void new_skiplist(SkipList **list, size_t max_height, int (*compare)(const void *, const void *)) {
    *list = (SkipList *)malloc(sizeof(SkipList));
    if (!*list) {
        fprintf(stderr, "Errore nell'allocazione della SkipList.\n");
        exit(EXIT_FAILURE);
    }
    (*list)->heads = (Node **)calloc(max_height, sizeof(Node *));
    if (!(*list)->heads) {
        fprintf(stderr, "Errore nell'allocazione dei puntatori iniziali.\n");
        exit(EXIT_FAILURE);
    }
    (*list)->max_level = 0;
    (*list)->max_height = max_height;
    (*list)->compare = compare;
    srand((unsigned int)time(NULL));
}

void clear_skiplist(SkipList **list) {
    if (*list) {
        for (size_t i = 0; i < (*list)->max_height; i++) {
            Node *current = (*list)->heads[i];
            while (current) {
                Node *temp = current;
                current = current->next[0];
                free(temp->next);
                free(temp);
            }
        }
        free((*list)->heads);
        free(*list);
        *list = NULL;
    }
}

void insert_skiplist(SkipList *list, void *item) {
    Node **update = (Node **)calloc((list->max_height + 1), sizeof(Node *));
    if (!update) {
        fprintf(stderr, "Errore nell'allocazione dell'array di aggiornamento.\n");
        exit(EXIT_FAILURE);
    }

    Node *x = &list->heads;
printf("sono prima del for \n");
if(x==NULL) printf("x è null, quindi list->heads è null\n");
    // loop invariant: x[i]->item <= item or item < first element of level i in list
    for (size_t i = list->max_level; i > 0; i--) {
        printf("sono ne for con i=%d\n",i);

        while (x->next[i - 1] != NULL && list->compare(x->next[i - 1]->item, item) <= 0) {
            printf("sono  nel while= %d \n",list->compare(x->next[i - 1]->item, item));
            x = x->next[i - 1];
        }
        printf("faccio update con i=%d \n",i);
        update[i] = x;
    }

    // loop end: x[1]->item <= item or item < first element in list

    x = x->next[0];

    if (x != NULL && list->compare(x->item, item) == 0) {
        // Elemento già presente, aggiorna il valore o gestisci il caso a tuo piacimento
        // x->item = newValue;
        free(update);
        return;
    }

    size_t level = random_level(list->max_height);

    if (level > list->max_level) {
        for (size_t i = list->max_level + 1; i <= level; i++) {
            printf("inizializzo update max level e level ",i,level);
            update[i]= &list->heads;
        }
        list->max_level = level;
    }

    x = create_node(item, level);

    for (size_t i = 1; i <= level; i++) {
        printf("i%d , level%d\n",i,level );
        x->next[i - 1] = update[i]->next[i - 1];
        update[i]->next[i - 1] = x;
    }

    free(update);
}

const void *search_skiplist(SkipList *list, void *item) {
    Node **x = list->heads;
    for (size_t i = list->max_level; i > 0; i--) {
        while (x[i - 1] != NULL && list->compare(x[i-1]->item, item) < 0) {
            x = x[i - 1]->next;
        }
    }

    if (x[0] != NULL && list->compare(x[0]->item, item) == 0) {
        return x[0]->item;
    } else {
        return NULL;
    }
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
            printf("%d [", current->item);

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